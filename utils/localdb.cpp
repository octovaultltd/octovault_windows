#include "localdb.h"

LocalDB::LocalDB()
{

}

// Firebase Configs...................................................


QString LocalDB::getLastOTP()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("LastOTP", QString()).toString();
}

void LocalDB::setLastOTP(QString otp)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("LastOTP", otp);
}

QString LocalDB::getResetTokenVerifyURL(){
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/octavaultvpn/resend-verification-token";
}

QString LocalDB::getResetURL()
{
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/reset-password";
}

QString LocalDB::getForgetURL()
{
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/octavaultvpn/forgot-password";
//    QSettings settings("OctoVault", "Kolpolok Limited");
//    return settings.value("ForgetURL", QString()).toString();
}

void LocalDB::setForgetURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ForgetURL", url);
}

QString LocalDB::getSignUpURL()
{
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/octavaultvpn/sign-up-free";
//    QSettings settings("OctoVault", "Kolpolok Limited");
//    return Encryption().getDecryptedString(settings.value("SignUpURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

QString LocalDB::getResendTokenURL()
{
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/octavaultvpn/resend-verification-token";
//    QSettings settings("OctoVault", "Kolpolok Limited");
//    return Encryption().getDecryptedString(settings.value("SignUpURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setSignUpURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("SignUpURL", url);
}

QString LocalDB::getTokenVerifyURL(){
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/octavaultvpn/token-verification";
}

QString LocalDB::getEmailSubscriptionURL()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return Encryption().getDecryptedString(settings.value("EmailSubscriptionURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setEmailSubscriptionURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("EmailSubscriptionURL", url);
}

QString LocalDB::getPaymentURL()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return Encryption().getDecryptedString(settings.value("PaymentURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setPaymentURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("PaymentURL", url);
}

QString LocalDB::getFeedbackSubmitURL()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return Encryption().getDecryptedString(settings.value("FeedbackSubmitURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setFeedbackSubmitURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("FeedbackSubmitURL", url);
}

QString LocalDB::getBuyPremiumNote()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("BuyPremiumNote", QString()).toString();
}

void LocalDB::setBuyPremiumNote(QString note)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("BuyPremiumNote", note);
}

QString LocalDB::getReferWithdrawURL()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return Encryption().getDecryptedString(settings.value("ReferWithdrawURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setReferWithdrawURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ReferWithdrawURL", url);
}

QString LocalDB::getReferInviteText()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("ReferInviteText", QString()).toString();
}

void LocalDB::setReferInviteText(QString text)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ReferInviteText", text);
}

QString LocalDB::getReferStatementURL()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return Encryption().getDecryptedString(settings.value("ReferStatementURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setReferStatementURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ReferStatementURL", url);
}

QString LocalDB::getFeedbackInfoURL()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return Encryption().getDecryptedString(settings.value("FeedbackInfoURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setFeedbackInfoURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("FeedbackInfoURL", url);
}

QString LocalDB::getReferSubmitURL()
{
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/use-referral-reseller";
//    QSettings settings("OctoVault", "Kolpolok Limited");
//    return Encryption().getDecryptedString(settings.value("ReferSubmitURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setReferSubmitURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ReferSubmitURL", url);
}

QString LocalDB::getDeviceInfoURL()
{
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/get-logged-in-devices";
//    QSettings settings("OctoVault", "Kolpolok Limited");
//    return Encryption().getDecryptedString(settings.value("DeviceInfoURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setDeviceInfoURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("DeviceInfoURL", url);
}

QString LocalDB::getDeleteAccountURL()
{
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/remove-user";
//    QSettings settings("OctoVault", "Kolpolok Limited");
//    return Encryption().getDecryptedString(settings.value("DeleteAccountURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setDeleteAccountURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("DeleteAccountURL", url);
}

QString LocalDB::getReferRefreshURL()
{
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/get-referral-info-reseller";
//    QSettings settings("OctoVault", "Kolpolok Limited");
//    return Encryption().getDecryptedString(settings.value("ReferRefreshURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setReferRefreshURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ReferRefreshURL", url);
}

QString LocalDB::getLoginURL()
{
    return "http://185.174.110.126:4041/vpn_api_v2_new/public/api_v2/login_v5";
//    QSettings settings("OctoVault", "Kolpolok Limited");
//    return Encryption().getDecryptedString(settings.value("LoginURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setLoginURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("LoginURL", url);
}

QString LocalDB::getPublicIPURL()
{
    return "https://ipinfo.io/json";
//    QSettings settings("OctoVault", "Kolpolok Limited");
//    return Encryption().getDecryptedString(settings.value("LoginURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setPublicIPURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("PublicIPURL", url);
}

QString LocalDB::getWhatsAppNumbers()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("WhatsAppNumbers", QString()).toString();
}

void LocalDB::setWhatsAppNumbers(QString numbers)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("WhatsAppNumbers", numbers);
}

bool LocalDB::isWalletEnabled()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("WalletEnabled", false).toBool();
}

void LocalDB::setWalletEnabled(bool enabled)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("WalletEnabled", enabled);
}

QString LocalDB::getCheckIpURL()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return Encryption().getDecryptedString(settings.value("CheckIpURL", QString()).toString(), CommonData().getFirestoreDecryptionKey());
}

void LocalDB::setCheckIpURL(QString url)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("CheckIpURL", url);
}

QString LocalDB::getReferPricing()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("ReferPricing", QString()).toString();
}

void LocalDB::setReferPricing(QString pricing)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ReferPricing", pricing);
}

// User Configs.......................................................
QString LocalDB::getUsername()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("Username", QString()).toString();
}

void LocalDB::setUsername(QString username)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("Username", username);
}

QString LocalDB::getPassword()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("Password", QString()).toString();
}

void LocalDB::setPassword(QString password)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("Password", password);
}

int LocalDB::getActiveServerID()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("ActiveServerID", 0).toInt();
}

void LocalDB::setActiveServerID(int ipID)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("RecentServerID", settings.value("ActiveServerID", 0).toInt());
    settings.setValue("ActiveServerID", ipID);
}

int LocalDB::getRecentServerID()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("RecentServerID", 0).toInt();
}

bool LocalDB::isLoggedIn()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("IsLoggedIn", false).toBool();
}

void LocalDB::setLoggedIn(bool isLoggedIn)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("IsLoggedIn", isLoggedIn);
}

QString LocalDB::getFavouritesList()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("FavList", "").toString();
}

void LocalDB::addFavourite(int ipID)
{
    QStringList list = getFavouritesList().split(",");
    list.append(QString::number(ipID));

    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("FavList", list.join(","));
}

void LocalDB::removeFavourite(int ipID)
{
    QString favList = getFavouritesList();
    QStringList list = favList.split(",");
    QStringList tempList = favList.split(",");
    for(int i = 0; i < list.size(); i ++){
        QString id = list.value(i);
        if(id == QString::number(ipID)){
            tempList.removeAt(i);
        }
    }

    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("FavList", tempList.join(","));
}

bool LocalDB::isFavServer(int ipID)
{
    QStringList list = getFavouritesList().split(",");
    if(list.contains(QString::number(ipID))){
        return true;
    }else{
        return false;
    }
}

int LocalDB::getExpireInDays()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("ExpireInDays", 0).toInt();
}

void LocalDB::setExpireInDays(int days)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ExpireInDays", days);
}

QString LocalDB::getValidityDate()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("ValidityDate", "").toString();
}

void LocalDB::setValidityDate(QString date)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ValidityDate", date);
}

QString LocalDB::getExpiryDate()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("ExpiryDate", "").toString();
}

void LocalDB::setExpiryDate(QString date)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ExpiryDate", date);
}

int LocalDB::getUserType()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("UserType", 0).toInt();
}

void LocalDB::setUserType(int type)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("UserType", type);
}

QString LocalDB::getUserStatus()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("UserStatus", "").toString();
}

void LocalDB::setUserStatus(QString status)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("UserStatus", status);
}

QString LocalDB::getContactEmail()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("ContactEmail", "").toString();
}

void LocalDB::setContactEmail(QString email)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ContactEmail", email);
}

int LocalDB::getNoticeType()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("NoticeType", 0).toInt();
}

void LocalDB::setNoticeType(int type)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("NoticeType", type);
}

QString LocalDB::getNoticeText()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("NoticeText", "").toString();
}

void LocalDB::setNoticeText(QString text)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("NoticeText", text);
}

double LocalDB::getNoticeStartTime()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("NoticeStartTime", 0).toDouble();
}

void LocalDB::setNoticeStartTime(double time)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("NoticeStartTime", time);
}

double LocalDB::getNoticeEndTime()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("NoticeEndTime", 0).toDouble();
}

void LocalDB::setNoticeEndTime(double time)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("NoticeEndTime", time);
}

QString LocalDB::getNoticeLockServerIds()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("NoticeLockServerIds", "").toString();
}

void LocalDB::setNoticeLockServerIds(QString ids)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("NoticeLockServerIds", ids);
}

bool LocalDB::isReferenceEnabled()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("ReferenceEnabled", false).toBool();
}

void LocalDB::setReferenceEnabled(bool enabled)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ReferenceEnabled", enabled);
}

QString LocalDB::getIPBundle()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("IPBundle", "").toString();
}

void LocalDB::setIPBundle(QString list)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("IPBundle", list);
}

QString LocalDB::getDeviceInfo()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("DeviceInfo", "").toString();
}

void LocalDB::setDeviceInfo(QString list)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("DeviceInfo", list);
}

QString LocalDB::getSelectedServerFilterTag()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("ServerFilterTag", "ALL").toString();
}

void LocalDB::setSelectedServerFiltertag(QString tag)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("ServerFilterTag", tag);
}

bool LocalDB::isFirstLaunch()
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    return settings.value("IsFirstLaunch", true).toBool();
}

void LocalDB::setFirstLaunch(bool isFirstLaunch)
{
    QSettings settings("OctoVault", "Kolpolok Limited");
    settings.setValue("IsFirstLaunch", isFirstLaunch);
}




