#include "commondata.h"
#include "utils/localdb.h"
#ifdef Q_OS_WIN
#include <wbemidl.h>
#include <comdef.h>
#endif

const QString FIRESTORE_DECRYPTION_KEY = "Ts(Trjslas";
const QString LOGIN_DECRYPTION_KEY = "Jufk8(fds";
const QString FIRESTORE_ENDPOINT = "https://firestore.googleapis.com/v1/projects/fvms-7036f/databases/(default)/documents/Symlex/lXT1i7zRv1ioEuyUkN81";

CommonData::CommonData()
{

}

QString CommonData::getAppName()
{
    return "OctoVault";
}

QString CommonData::getAppVersion()
{
    return "1.0.0";
}

QPair<QString, QString> CommonData::getManufacturerAndModel()
{
    // <Manufacturer, Model>
    QPair<QString,QString> retVal("Unknown", "Unknown");

    // TODO: Implement Cross-platform
#ifdef Q_OS_WIN
    IWbemLocator *locator = nullptr;
    IWbemServices *services = nullptr;
    auto hResult = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast<LPVOID *>(&locator));

    auto hasFailed = [&hResult]() {
        if (FAILED(hResult)) {
            auto error = _com_error(hResult);
            qDebug()<< QString::fromWCharArray(error.ErrorMessage());
            return true;
        }
        return false;
    };

    auto getValue = [&hResult, &hasFailed](IWbemClassObject *classObject, LPCWSTR property) {
        QString propertyValueText = "Unknown";
        VARIANT propertyValue;
        hResult = classObject->Get(property, 0, &propertyValue, nullptr, nullptr);
        if (!hasFailed()) {
            if ((propertyValue.vt == VT_NULL) || (propertyValue.vt == VT_EMPTY)) {
            } else if (propertyValue.vt & VT_ARRAY) {
                propertyValueText = "Unknown"; //Array types not supported
            } else {
                propertyValueText = QString::fromWCharArray(propertyValue.bstrVal,static_cast<int>(::SysStringLen(propertyValue.bstrVal)));
            }
        }
        VariantClear(&propertyValue);
        return propertyValueText;
    };

    QString manufacturer = "Unknown";
    QString model = "Unknown";
    if (!hasFailed()) {
        // Connect to the root\cimv2 namespace with the current user and obtain pointer pSvc to make IWbemServices calls.
        hResult = locator->ConnectServer(SysAllocString(L"ROOT\\CIMV2"), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &services);

        if (!hasFailed()) {
            // Set the IWbemServices proxy so that impersonation of the user (client) occurs.
            hResult = CoSetProxyBlanket(services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL,
                                        RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);

            if (!hasFailed()) {
                IEnumWbemClassObject* classObjectEnumerator = nullptr;
                hResult = services->ExecQuery(SysAllocString(L"WQL"), SysAllocString(L"SELECT * FROM Win32_ComputerSystem"), WBEM_FLAG_FORWARD_ONLY |
                                                                                                                                 WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &classObjectEnumerator);
                if (!hasFailed()) {
                    IWbemClassObject *classObject;
                    ULONG uReturn = 0;
                    hResult = classObjectEnumerator->Next(static_cast<long>(WBEM_INFINITE), 1, &classObject, &uReturn);
                    if (uReturn != 0) {
                        manufacturer = getValue(classObject, static_cast<LPCWSTR>(L"Manufacturer"));
                        model = getValue(classObject, static_cast<LPCWSTR>(L"Model"));
                        retVal.first = manufacturer;
                        retVal.second = model;
                    }
                    classObject->Release();
                }
                classObjectEnumerator->Release();
            }
        }
    }

    if (locator) {
        locator->Release();
    }
    if (services) {
        services->Release();
    }
    CoUninitialize();
#endif

#ifdef Q_OS_MACOS
    retVal.first = "Apple";
    retVal.second = "MacOS";
#endif

    return retVal;
}

QString CommonData::getCurrentTimeZone()
{
    const auto t1 = QDateTime::currentDateTime();
    const auto t2 = QDateTime(t1.date(), t1.time(),Qt::UTC);

    QString prefix = "+";
    if(t1 > t2)
        prefix = "-";

    auto dt = t1.secsTo(t2);

    QTime t(0,0);
    t = t.addSecs(static_cast<int>(dt));

    auto tz = prefix + t.toString("hh:mm");

    return tz;
}

int CommonData::getCurrentCountryCallingCode()
{
    QMap<QString, int> map;

    QFile file(":/misc/country_calling_code_map.txt");

    if(file.open(QFile::ReadOnly))
    {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            QString line = stream.readLine();
            auto data = line.split(",");

            auto country = data.at(0);
            country = country.replace("\"", "");
            country = country.simplified();
            country = country.toLower();

            map.insert(country, data.at(1).toInt());
        }
    }

    auto country = QLocale::countryToString(QDateTime::currentDateTime().timeZone().country()).toLower();

    if(map.contains(country))
        return map.value(country);

    return -1;
}

QString CommonData::getLoginDecryptionKey()
{
    return LOGIN_DECRYPTION_KEY;
}

QString CommonData::getFirestoreDecryptionKey()
{
    return FIRESTORE_DECRYPTION_KEY;
}

QString CommonData::getFireStoreEndpoint()
{
    return FIRESTORE_ENDPOINT;
}

QString CommonData::getFlagImage(int countryCode)
{
    switch (countryCode) {
    case 4: //afghanistan
        return ":/flags/flags/flag_afghanistan.png";
    case 8: //albania
        return ":/flags/flags/flag_albania.png";
    case 12: //algeria
        return ":/flags/flags/flag_algeria.png";
    case 20: //andorra
        return ":/flags/flags/flag_andorra.png";
    case 24: //angola
        return ":/flags/flags/flag_angola.png";
    case 10: //antarctica
        return ":/flags/flags/flag_antarctica.png";
    case 32: //argentina
        return ":/flags/flags/flag_argentina.png";
    case 51: //armenia
        return ":/flags/flags/flag_armenia.png";
    case 533: //aruba
        return ":/flags/flags/flag_aruba.png";
    case 36: //australia
        return ":/flags/flags/flag_australia.png";
    case 40: //austria
        return ":/flags/flags/flag_austria.png";
    case 31: //azerbaijan
        return ":/flags/flags/flag_azerbaijan.png";
    case 48: //bahrain
        return ":/flags/flags/flag_bahrain.png";
    case 50: //bangladesh
        return ":/flags/flags/flag_bangladesh.png";
    case 112: //belarus
        return ":/flags/flags/flag_belarus.png";
    case 56: //belgium
        return ":/flags/flags/flag_belgium.png";
    case 84: //belize
        return ":/flags/flags/flag_belize.png";
    case 204: //benin
        return ":/flags/flags/flag_benin.png";
    case 64: //bhutan
        return ":/flags/flags/flag_bhutan.png";
    case 68: //bolivia, plurinational state of
        return ":/flags/flags/flag_bolivia.png";
    case 70: //bosnia and herzegovina
        return ":/flags/flags/flag_bosnia.png";
    case 72: //botswana
        return ":/flags/flags/flag_botswana.png";
    case 76: //brazil
        return ":/flags/flags/flag_brazil.png";
    case 96: //brunei darussalam
        return ":/flags/flags/flag_brunei.png";
    case 100: //bulgaria
        return ":/flags/flags/flag_bulgaria.png";
    case 854: //burkina faso
        return ":/flags/flags/flag_burkina_faso.png";
    case 104: //myanmar
        return ":/flags/flags/flag_myanmar.png";
    case 108: //burundi
        return ":/flags/flags/flag_burundi.png";
    case 116: //cambodia
        return ":/flags/flags/flag_cambodia.png";
    case 120: //cameroon
        return ":/flags/flags/flag_cameroon.png";
    case 124: //canada
        return ":/flags/flags/flag_canada.png";
    case 132: //cape verde......
        return ":/flags/flags/flag_cape_verde.png";
    case 140: //central african republic
        return ":/flags/flags/flag_central_african_republic.png";
    case 148: //chad
        return ":/flags/flags/flag_chad.png";
    case 152: //chile
        return ":/flags/flags/flag_chile.png";
    case 156: //china
        return ":/flags/flags/flag_china.png";
    case 170: //colombia
        return ":/flags/flags/flag_colombia.png";
    case 174: //comoros
        return ":/flags/flags/flag_comoros.png";
    case 178: //congo
        return ":/flags/flags/flag_republic_of_the_congo.png";
    case 180: //congo, the democratic republic of the
        return ":/flags/flags/flag_democratic_republic_of_the_congo.png";
    case 184: //cook islands
        return ":/flags/flags/flag_cook_islands.png";
    case 188: //costa rica
        return ":/flags/flags/flag_costa_rica.png";
    case 191: //croatia
        return ":/flags/flags/flag_croatia.png";
    case 192: //cuba
        return ":/flags/flags/flag_cuba.png";
    case 196: //cyprus
        return ":/flags/flags/flag_cyprus.png";
    case 203: //czech republic
        return ":/flags/flags/flag_czech_republic.png";
    case 208: //denmark
        return ":/flags/flags/flag_denmark.png";
    case 262: //djibouti
        return ":/flags/flags/flag_djibouti.png";
    case 626: //timor-leste
        return ":/flags/flags/flag_timor_leste.png";
    case 218: //ecuador
        return ":/flags/flags/flag_ecuador.png";
    case 818: //egypt
        return ":/flags/flags/flag_egypt.png";
    case 222: //el salvador
        return ":/flags/flags/flag_el_salvador.png";
    case 226: //equatorial guinea
        return ":/flags/flags/flag_equatorial_guinea.png";
    case 232: //eritrea
        return ":/flags/flags/flag_eritrea.png";
    case 233: //estonia
        return ":/flags/flags/flag_estonia.png";
    case 231: //ethiopia
        return ":/flags/flags/flag_ethiopia.png";
    case 238: //falkland islands (malvinas)
        return ":/flags/flags/flag_falkland_islands.png";
    case 234: //faroe islands
        return ":/flags/flags/flag_faroe_islands.png";
    case 242: //fiji
        return ":/flags/flags/flag_fiji.png";
    case 246: //finland
        return ":/flags/flags/flag_finland.png";
    case 250: //france
        return ":/flags/flags/flag_france.png";
    case 258: //french polynesia
        return ":/flags/flags/flag_french_polynesia.png";
    case 266: //gabon
        return ":/flags/flags/flag_gabon.png";
    case 270: //gambia
        return ":/flags/flags/flag_gambia.png";
    case 268: //georgia
        return ":/flags/flags/flag_georgia.png";
    case 276: //germany
        return ":/flags/flags/flag_germany.png";
    case 288: //ghana
        return ":/flags/flags/flag_ghana.png";
    case 292: //gibraltar
        return ":/flags/flags/flag_gibraltar.png";
    case 300: //greece
        return ":/flags/flags/flag_greece.png";
    case 304: //greenland
        return ":/flags/flags/flag_greenland.png";
    case 320: //guatemala
        return ":/flags/flags/flag_guatemala.png";
    case 324: //guinea
        return ":/flags/flags/flag_guinea.png";
    case 624: //guinea-bissau
        return ":/flags/flags/flag_guinea_bissau.png";
    case 328: //guyana
        return ":/flags/flags/flag_guyana.png";
    case 332: //haiti
        return ":/flags/flags/flag_haiti.png";
    case 340: //honduras
        return ":/flags/flags/flag_honduras.png";
    case 344: //hong kong
        return ":/flags/flags/flag_hong_kong.png";
    case 348: //hungary
        return ":/flags/flags/flag_hungary.png";
    case 356: //india
        return ":/flags/flags/flag_india.png";
    case 360: //indonesia
        return ":/flags/flags/flag_indonesia.png";
    case 364: //iran, islamic republic of
        return ":/flags/flags/flag_iran.png";
    case 368: //iraq
        return ":/flags/flags/flag_iraq.png";
    case 372: //ireland
        return ":/flags/flags/flag_ireland.png";
    case 833: //isle of man
        return ":/flags/flags/flag_isleof_man.png";
    case 376: //israel
        return ":/flags/flags/flag_israel.png";
    case 380: //italy
        return ":/flags/flags/flag_italy.png";
    case 384: //côte d\'ivoire
        return ":/flags/flags/flag_cote_divoire.png";
    case 392: //japan
        return ":/flags/flags/flag_japan.png";
    case 400: //jordan
        return ":/flags/flags/flag_jordan.png";
    case 398: //kazakhstan
        return ":/flags/flags/flag_kazakhstan.png";
    case 404: //kenya
        return ":/flags/flags/flag_kenya.png";
    case 296: //kiribati
        return ":/flags/flags/flag_kiribati.png";
    case 414: //kuwait
        return ":/flags/flags/flag_kuwait.png";
    case 417: //kyrgyzstan
        return ":/flags/flags/flag_kyrgyzstan.png";
    case 136: // Cayman Islands
        return ":/flags/flags/flag_cayman_islands.png";
    case 418: //lao people\'s democratic republic
        return ":/flags/flags/flag_laos.png";
    case 428: //latvia
        return ":/flags/flags/flag_latvia.png";
    case 422: //lebanon
        return ":/flags/flags/flag_lebanon.png";
    case 426: //lesotho
        return ":/flags/flags/flag_lesotho.png";
    case 430: //liberia
        return ":/flags/flags/flag_liberia.png";
    case 434: //libya
        return ":/flags/flags/flag_libya.png";
    case 438: //liechtenstein
        return ":/flags/flags/flag_liechtenstein.png";
    case 440: //lithuania
        return ":/flags/flags/flag_lithuania.png";
    case 442: //luxembourg
        return ":/flags/flags/flag_luxembourg.png";
    case 446: //macao
        return ":/flags/flags/flag_macao.png";
    case 450: //madagascar
        return ":/flags/flags/flag_madagascar.png";
    case 454: //malawi
        return ":/flags/flags/flag_malawi.png";
    case 458: //malaysia
        return ":/flags/flags/flag_malaysia.png";
    case 462: //maldives
        return ":/flags/flags/flag_maldives.png";
    case 466: //mali
        return ":/flags/flags/flag_mali.png";
    case 470: //malta
        return ":/flags/flags/flag_malta.png";
    case 584: //marshall islands
        return ":/flags/flags/flag_marshall_islands.png";
    case 478: //mauritania
        return ":/flags/flags/flag_mauritania.png";
    case 480: //mauritius
        return ":/flags/flags/flag_mauritius.png";
    case 175: //mayotte
        return ":/flags/flags/flag_martinique.png"; // no exact flag found
    case 474: //martinique
        return ":/flags/flags/flag_martinique.png";
    case 484: //mexico
        return ":/flags/flags/flag_mexico.png";
    case 583: //micronesia, federated states of
        return ":/flags/flags/flag_micronesia.png";
    case 498: //moldova, republic of
        return ":/flags/flags/flag_moldova.png";
    case 492: //monaco
        return ":/flags/flags/flag_monaco.png";
    case 496: //mongolia
        return ":/flags/flags/flag_mongolia.png";
    case 499: //montenegro
        return ":/flags/flags/flag_of_montenegro.png";// custom
    case 504: //morocco
        return ":/flags/flags/flag_morocco.png";
    case 508: //mozambique
        return ":/flags/flags/flag_mozambique.png";
    case 516: //namibia
        return ":/flags/flags/flag_namibia.png";
    case 520: //nauru
        return ":/flags/flags/flag_nauru.png";
    case 524: //nepal
        return ":/flags/flags/flag_nepal.png";
    case 528: //netherlands
        return ":/flags/flags/flag_netherlands.png";
    case 540: //new caledonia
        return ":/flags/flags/flag_new_caledonia.png";
    case 554: //new zealand
        return ":/flags/flags/flag_new_zealand.png";
    case 558: //nicaragua
        return ":/flags/flags/flag_nicaragua.png";
    case 562: //niger
        return ":/flags/flags/flag_niger.png";
    case 566: //nigeria
        return ":/flags/flags/flag_nigeria.png";
    case 570: //niue
        return ":/flags/flags/flag_niue.png";
    case 410: //north korea
        return ":/flags/flags/flag_north_korea.png";
    case 578: //norway
        return ":/flags/flags/flag_norway.png";
    case 512: //oman
        return ":/flags/flags/flag_oman.png";
    case 586: //pakistan
        return ":/flags/flags/flag_pakistan.png";
    case 585: //palau
        return ":/flags/flags/flag_palau.png";
    case 591: //panama
        return ":/flags/flags/flag_panama.png";
    case 598: //papua new guinea
        return ":/flags/flags/flag_papua_new_guinea.png";
    case 600: //paraguay
        return ":/flags/flags/flag_paraguay.png";
    case 604: //peru
        return ":/flags/flags/flag_peru.png";
    case 608: //philippines
        return ":/flags/flags/flag_philippines.png";
    case 612: //pitcairn
        return ":/flags/flags/flag_pitcairn_islands.png";
    case 616: //poland
        return ":/flags/flags/flag_poland.png";
    case 620: //portugal
        return ":/flags/flags/flag_portugal.png";
    case 630: //puerto rico
        return ":/flags/flags/flag_puerto_rico.png";
    case 634: //qatar
        return ":/flags/flags/flag_qatar.png";
    case 642: //romania
        return ":/flags/flags/flag_romania.png";
    case 643: //russian federation
        return ":/flags/flags/flag_russian_federation.png";
    case 646: //rwanda
        return ":/flags/flags/flag_rwanda.png";
    case 652: //saint barthélemy
        return ":/flags/flags/flag_saint_barthelemy.png";// custom
    case 882: //samoa
        return ":/flags/flags/flag_samoa.png";
    case 674: //san marino
        return ":/flags/flags/flag_san_marino.png";
    case 678: //sao tome and principe
        return ":/flags/flags/flag_sao_tome_and_principe.png";
    case 682: //saudi arabia
        return ":/flags/flags/flag_saudi_arabia.png";
    case 686: //senegal
        return ":/flags/flags/flag_senegal.png";
    case 688: //serbia
        return ":/flags/flags/flag_serbia.png"; // custom
    case 690: //seychelles
        return ":/flags/flags/flag_seychelles.png";
    case 694: //sierra leone
        return ":/flags/flags/flag_sierra_leone.png";
    case 702: //singapore
        return ":/flags/flags/flag_singapore.png";
    case 703: //slovakia
        return ":/flags/flags/flag_slovakia.png";
    case 705: //slovenia
        return ":/flags/flags/flag_slovenia.png";
    case 90: //solomon islands
        return ":/flags/flags/flag_soloman_islands.png";
    case 706: //somalia
        return ":/flags/flags/flag_somalia.png";
    case 710: //south africa
        return ":/flags/flags/flag_south_africa.png";
    case 408: //south korea
        return ":/flags/flags/flag_south_korea.png";
    case 724: //spain
        return ":/flags/flags/flag_spain.png";
    case 144: //sri lanka
        return ":/flags/flags/flag_sri_lanka.png";
    case 654: //saint helena, ascension and tristan da cunha
        return ":/flags/flags/flag_saint_helena.png"; // custom
    case 666: //saint pierre and miquelon
        return ":/flags/flags/flag_saint_pierre.png";
    case 729: //sudan
        return ":/flags/flags/flag_sudan.png";
    case 740: //suriname
        return ":/flags/flags/flag_suriname.png";
    case 752: //sweden
        return ":/flags/flags/flag_sweden.png";
    case 756: //switzerland
        return ":/flags/flags/flag_switzerland.png";
    case 760: //syrian arab republic
        return ":/flags/flags/flag_syria.png";
    case 158: //taiwan, province of china
        return ":/flags/flags/flag_taiwan.png";
    case 762: //tajikistan
        return ":/flags/flags/flag_tajikistan.png";
    case 834: //tanzania, united republic of
        return ":/flags/flags/flag_tanzania.png";
    case 764: //thailand
        return ":/flags/flags/flag_thailand.png";
    case 768: //togo
        return ":/flags/flags/flag_togo.png";
    case 772: //tokelau
        return ":/flags/flags/flag_tokelau.png";
    case 776: //tonga
        return ":/flags/flags/flag_tonga.png";
    case 788: //tunisia
        return ":/flags/flags/flag_tunisia.png";
    case 792: //turkey
        return ":/flags/flags/flag_turkey.png";
    case 795: //turkmenistan
        return ":/flags/flags/flag_turkmenistan.png";
    case 798: //tuvalu
        return ":/flags/flags/flag_tuvalu.png";
    case 784: //united arab emirates
        return ":/flags/flags/flag_uae.png";
    case 800: //uganda
        return ":/flags/flags/flag_uganda.png";
    case 826: //united kingdom
        return ":/flags/flags/flag_united_kingdom.png";
    case 804: //ukraine
        return ":/flags/flags/flag_ukraine.png";
    case 858: //uruguay
        return ":/flags/flags/flag_uruguay.png";
    case 840: //united states
        return ":/flags/flags/flag_united_states_of_america.png";
    case 860: //uzbekistan
        return ":/flags/flags/flag_uzbekistan.png";
    case 548: //vanuatu
        return ":/flags/flags/flag_vanuatu.png";
    case 862: //venezuela, bolivarian republic of
        return ":/flags/flags/flag_venezuela.png";
    case 704: //vietnam
        return ":/flags/flags/flag_vietnam.png";
    case 876: //wallis and futuna
        return ":/flags/flags/flag_wallis_and_futuna.png";
    case 887: //yemen
        return ":/flags/flags/flag_yemen.png";
    case 894: //zambia
        return ":/flags/flags/flag_zambia.png";
    case 716: //zimbabwe
        return ":/flags/flags/flag_zimbabuwe.png";

    // Caribbean Islands
    case 660: //anguilla
        return ":/flags/flags/flag_anguilla.png";
    case 28: //antigua & barbuda
        return ":/flags/flags/flag_antigua_and_barbuda.png";
    case 44: //bahamas
        return ":/flags/flags/flag_bahamas.png";
    case 52: //barbados
        return ":/flags/flags/flag_barbados.png";
    case 92: //british virgin islands
        return ":/flags/flags/flag_british_virgin_islands.png";
    case 212: //dominica
        return ":/flags/flags/flag_dominica";
    case 214: //dominican republic
        return ":/flags/flags/flag_dominican_republic.png";
    case 308: //grenada
        return ":/flags/flags/flag_grenada.png";
    case 388: //jamaica
        return ":/flags/flags/flag_jamaica.png";
    case 500: //montserrat
        return ":/flags/flags/flag_montserrat.png";
    case 659: //st kitts & nevis
        return ":/flags/flags/flag_saint_kitts_and_nevis.png";
    case 662: //st lucia
        return ":/flags/flags/flag_saint_lucia.png";
    case 670: //st vincent & the grenadines
        return ":/flags/flags/flag_saint_vicent_and_the_grenadines.png";
    case 780: //trinidad & tobago
        return ":/flags/flags/flag_trinidad_and_tobago.png";
    case 796: //turks & caicos islands
        return ":/flags/flags/flag_turks_and_caicos_islands.png";
    case 850: //us virgin islands
        return ":/flags/flags/flag_us_virgin_islands.png";
    case 728: // south sudan
        return ":/flags/flags/flag_south_sudan.png";
    default:
        return "";
    }
}

std::shared_ptr<OpenConnectConnection> CommonData::getVPNConnection(){
    static std::shared_ptr<OpenConnectConnection> conn(new OpenConnectConnection);
    return conn;
}

QJsonObject CommonData::getServerByIPID(int ipID){
    QString bundles = LocalDB().getIPBundle();
    QJsonDocument doc = QJsonDocument::fromJson(bundles.toUtf8());
    QJsonArray serverArray = doc.array();
    for(int i = 0; i <serverArray.size(); i ++){
        QJsonObject server = serverArray.at(i).toObject();
        if(server.value("ip_id").toInt() == ipID){
            return server;
        }
    }
    return serverArray.at(0).toObject();
}


