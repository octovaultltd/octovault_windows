#include "networkmanager.h"

NetworkManager::NetworkManager()
{

}

QString NetworkManager::getFirestoreData()
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(CommonData().getFireStoreEndpoint());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    if (reply->error()) {
        qDebug() << reply->errorString();
        return reply->errorString();
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            return "Empty Firestore";
        }else{
            QJsonObject mainObject = doc.object();
            QJsonObject fieldsObject = mainObject.value("fields").toObject();

            QJsonObject forgetURLObject = fieldsObject.value("ForgotPasswordURL").toObject();
            QJsonObject signUpURLObject = fieldsObject.value("SignUpURL").toObject();
            QJsonObject emailSubscriptionURLObject = fieldsObject.value("EmailSubscriptionURL").toObject();
            QJsonObject paymentURLObject = fieldsObject.value("PaymentURL").toObject();
            QJsonObject feedbackSubmitURLObject = fieldsObject.value("FeedbackSubmitURL").toObject();
            QJsonObject buyPremiumNoteObject = fieldsObject.value("BuyPremiumNote").toObject();
            QJsonObject referWithdrawURLObject = fieldsObject.value("ReferWithdrawURL").toObject();
            QJsonObject referInviteTextObject = fieldsObject.value("ReferInviteText").toObject();
            QJsonObject referStatementURLObject = fieldsObject.value("ReferStatementURL").toObject();
            QJsonObject feedbackInfoURLObject = fieldsObject.value("FeedbackInfoURL").toObject();
            QJsonObject referSubmitURLObject = fieldsObject.value("ReferSubmitURL").toObject();
            QJsonObject deviceInfoURLObject = fieldsObject.value("DeviceInfoURL").toObject();
            QJsonObject deleteAccountURLObject = fieldsObject.value("DeleteAccountURL").toObject();
            QJsonObject referRefreshURLObject = fieldsObject.value("ReferRefreshURL").toObject();
            QJsonObject loginURLObject = fieldsObject.value("LoginURL").toObject();
            QJsonObject whatsAppNumbersObject = fieldsObject.value("WhatsAppNumbers").toObject();
            QJsonObject isWalletEnabledObject = fieldsObject.value("IsWalletEnabled").toObject();
            QJsonObject checkIpURLObject = fieldsObject.value("CheckIPURL").toObject();
            QJsonObject referPricingObject = fieldsObject.value("ReferPricing").toObject();

            QString forgetURL = forgetURLObject.value("stringValue").toString();
            QString signUpURL = signUpURLObject.value("stringValue").toString();
            QString emailSubscriptionURL = emailSubscriptionURLObject.value("stringValue").toString();
            QString paymentURL = paymentURLObject.value("stringValue").toString();
            QString feedbackSubmitURL = feedbackSubmitURLObject.value("stringValue").toString();
            QString buyPremiumNote = buyPremiumNoteObject.value("stringValue").toString();
            QString referWithdrawURL = referWithdrawURLObject.value("stringValue").toString();
            QString referInviteText = referInviteTextObject.value("stringValue").toString();
            QString referStatementURL = referStatementURLObject.value("stringValue").toString();
            QString feedbackInfoURL = feedbackInfoURLObject.value("stringValue").toString();
            QString referSubmitURL = referSubmitURLObject.value("stringValue").toString();
            QString deviceInfoURL = deviceInfoURLObject.value("stringValue").toString();
            QString deleteAccountURL = deleteAccountURLObject.value("stringValue").toString();
            QString referRefreshURL = referRefreshURLObject.value("stringValue").toString();
            QString loginURL = loginURLObject.value("stringValue").toString();
            QString whatsAppNumbers = whatsAppNumbersObject.value("stringValue").toString();
            bool isWalletEnabled = isWalletEnabledObject.value("booleanValue").toBool();
            QString checkIpURL = checkIpURLObject.value("stringValue").toString();
            QString referPricing = referPricingObject.value("stringValue").toString();

            LocalDB().setForgetURL(forgetURL);
            LocalDB().setSignUpURL(signUpURL);
            LocalDB().setEmailSubscriptionURL(emailSubscriptionURL);
            LocalDB().setPaymentURL(paymentURL);
            LocalDB().setFeedbackSubmitURL(feedbackSubmitURL);
            LocalDB().setBuyPremiumNote(buyPremiumNote);
            LocalDB().setReferWithdrawURL(referWithdrawURL);
            LocalDB().setReferInviteText(referInviteText);
            LocalDB().setReferStatementURL(referStatementURL);
            LocalDB().setFeedbackInfoURL(feedbackInfoURL);
            LocalDB().setReferSubmitURL(referSubmitURL);
            LocalDB().setDeviceInfoURL(deviceInfoURL);
            LocalDB().setDeleteAccountURL(deleteAccountURL);
            LocalDB().setReferRefreshURL(referRefreshURL);
            LocalDB().setLoginURL(loginURL);
            LocalDB().setWhatsAppNumbers(whatsAppNumbers);
            LocalDB().setWalletEnabled(isWalletEnabled);
            LocalDB().setCheckIpURL(checkIpURL);
            LocalDB().setReferPricing(referPricing);

            return "Success";
        }
    }
}

QVector<QString> NetworkManager::callLoginAPI(QString username, QString password)
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();

    QUrlQuery requestData;
    requestData.addQueryItem("username", "HR4411-"+username);
    requestData.addQueryItem("pass", password);
    requestData.addQueryItem("udid", QSysInfo::machineUniqueId());
    requestData.addQueryItem("vpnAppVersion", CommonData().getAppVersion());
    requestData.addQueryItem("brand", CommonData().getManufacturerAndModel().first);
    requestData.addQueryItem("osName", QSysInfo::productType());
    requestData.addQueryItem("osVersion", QSysInfo::productVersion());
#ifdef Q_OS_WIN
    requestData.addQueryItem("device_type", "3");
#endif
#ifdef Q_OS_MACOS
    requestData.addQueryItem("device_type", "4");
#endif
    requestData.addQueryItem("countryCode", QString::number(CommonData::getCurrentCountryCallingCode()));
    requestData.addQueryItem("model", CommonData().getManufacturerAndModel().second);
    requestData.addQueryItem("osPlatform", QSysInfo::productType());
    requestData.addQueryItem("inAppPurchase", "1");

    QNetworkRequest request(LocalDB().getLoginURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->post(request, requestData.query(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    qDebug()<< reply;

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty Login Response");
            return replyData;
        }else{
            QJsonObject response = doc.object();
            int responseCode = response.value("response_code").toInt();
            int statusCode = response.value("status_code").toInt();
            QString message = response.value("message").toString();
            replyData.append(QString::number(responseCode));
            replyData.append(message);
            replyData.append(QString::number(statusCode));
            if(responseCode == 1){
                CommonData::getVPNConnection()->setUsername(username);
                CommonData::getVPNConnection()->setPassword(password);
                LocalDB().setLoggedIn(true);
                LocalDB().setUsername(username);
                LocalDB().setPassword(password);
                LocalDB().setExpireInDays(response.value("expire_in_days").toInt());
                LocalDB().setValidityDate(response.value("validity_date").toString());
                LocalDB().setExpiryDate(response.value("expired_at").toString());
                LocalDB().setUserType(response.value("user_type").toInt());
                LocalDB().setUserStatus(response.value("user_status").toString());
                LocalDB().setContactEmail(response.value("contact_email").toString());
                LocalDB().setNoticeType(response.value("notice_type").toInt());
                LocalDB().setNoticeText(response.value("notice").toString());
                LocalDB().setNoticeStartTime(response.value("start_after").toDouble());
                LocalDB().setNoticeEndTime(response.value("end_after").toDouble());
                LocalDB().setNoticeLockServerIds(response.value("lock_servers_id").toString());
                LocalDB().setReferenceEnabled(response.value("allow_referrence_feature").toBool());
                QJsonDocument array;
                array.setArray(response.value("ip_bundle").toArray());
                LocalDB().setIPBundle(array.toJson());
            }
            return replyData;
        }
    }
}

QVector<QString> NetworkManager::callSignUpAPI(QString username, QString password)
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrlQuery requestData;
    requestData.addQueryItem("username", "HR4411-"+username);
    requestData.addQueryItem("password", password);
    requestData.addQueryItem("verification_type", "2");
    requestData.addQueryItem("otp_length", "4");
    QNetworkRequest request(LocalDB().getSignUpURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->post(request, requestData.query(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty SignUp Response");
            return replyData;
        }else{
            auto response = doc.object();
            auto responseCode = response.value("response_code").toInt();
            QString message = response.value("message").toString();
            replyData.append(QString::number(responseCode));
            replyData.append(message);
            if(responseCode == 1){
                LocalDB().setUsername(username);
                LocalDB().setPassword(password);
            }
            return replyData;
        }
    }
}

QVector<QString> NetworkManager::callResendTokenAPI(QString username)
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrlQuery requestData;
    requestData.addQueryItem("username", "HR4411-"+username);
    requestData.addQueryItem("verification_type", "2");
    QNetworkRequest request(LocalDB().getResendTokenURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->post(request, requestData.query(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty Resend Email Verify Response");
            return replyData;
        }else{
            auto response = doc.object();
            auto responseCode = response.value("response_code").toInt();
            QString message = response.value("message").toString();
            replyData.append(QString::number(responseCode));
            replyData.append(message);
            return replyData;
        }
    }
}

QVector<QString> NetworkManager::callTokenVerifyAPI(QString username, QString token, QString type)
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrlQuery requestData;
    requestData.addQueryItem("username", "HR4411-"+username);
    requestData.addQueryItem("token", token);
    requestData.addQueryItem("is_destroy_token", "2");
    requestData.addQueryItem("token_type", type);
    QNetworkRequest request(LocalDB().getTokenVerifyURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->post(request, requestData.query(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty Token Verify Response");
            return replyData;
        }else{
            auto response = doc.object();
            auto responseCode = response.value("response_code").toInt();
            QString message = response.value("message").toString();
            replyData.append(QString::number(responseCode));
            replyData.append(message);
            return replyData;
        }
    }
}

QVector<QString> NetworkManager::callForgetAPI(QString username)
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrlQuery requestData;
    requestData.addQueryItem("username", "HR4411-"+username);
    requestData.addQueryItem("verification_type", "2");
    requestData.addQueryItem("otp_length", "4");
    QNetworkRequest request(LocalDB().getForgetURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->post(request, requestData.query(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty Forget Response");
            return replyData;
        }else{
            auto response = doc.object();
            auto responseCode = response.value("response_code").toInt();
            QString message = response.value("message").toString();
            replyData.append(QString::number(responseCode));
            replyData.append(message);
            return replyData;
        }
    }
}

QVector<QString> NetworkManager::callResetAPI(QString username, QString token, QString password, QString password_confirmation)
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrlQuery requestData;
    requestData.addQueryItem("username", "HR4411-"+username);
    requestData.addQueryItem("token", token);
    requestData.addQueryItem("password", password);
    requestData.addQueryItem("password_confirmation", password_confirmation);
    QNetworkRequest request(LocalDB().getResetURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->post(request, requestData.query(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty Reset Response");
            return replyData;
        }else{
            auto response = doc.object();
            auto responseCode = response.value("response_code").toInt();
            QString message = response.value("message").toString();
            replyData.append(QString::number(responseCode));
            replyData.append(message);
            return replyData;
        }
    }
}

QVector<QString> NetworkManager::callResetTokenVerifyAPI(QString username)
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrlQuery requestData;
    requestData.addQueryItem("username", "HR4411-"+username);
    requestData.addQueryItem("verification_type", "2");
    QNetworkRequest request(LocalDB().getResetTokenVerifyURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->post(request, requestData.query(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty Reset Token Verify Response");
            return replyData;
        }else{
            auto response = doc.object();
            auto responseCode = response.value("response_code").toInt();
            QString message = response.value("message").toString();
            replyData.append(QString::number(responseCode));
            replyData.append(message);
            return replyData;
        }
    }
}

QVector<QString> NetworkManager::callDeviceInfoAPI()
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrlQuery requestData;
    requestData.addQueryItem("username", "HR4411-"+LocalDB::getUsername());
    requestData.addQueryItem("pass", LocalDB::getPassword());
    requestData.addQueryItem("udid", QSysInfo::machineUniqueId());
    requestData.addQueryItem("noEcrypted", "1");
    QNetworkRequest request(LocalDB().getDeviceInfoURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->post(request, requestData.query(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty DeviceInfo Response");
            return replyData;
        }else{
            auto response = doc.object();
            auto responseCode = response.value("response_code").toInt();
            QString message = response.value("message").toString();
            replyData.append(QString::number(responseCode));
            replyData.append(message);
            if(responseCode == 1){
                QJsonDocument array;
                array.setArray(response.value("data").toArray());
                LocalDB().setDeviceInfo(array.toJson());
            }
            return replyData;
        }
    }
}

QVector<QString> NetworkManager::callDeleteAccountAPI()
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrlQuery requestData;
    requestData.addQueryItem("username", "HR4411-"+LocalDB::getUsername());
    requestData.addQueryItem("pass", LocalDB::getPassword());
    requestData.addQueryItem("udid", QSysInfo::machineUniqueId());
    requestData.addQueryItem("noEcrypted", "1");
    QNetworkRequest request(LocalDB().getDeleteAccountURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->post(request, requestData.query(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty DeleteAccount Response");
            return replyData;
        }else{
            auto response = doc.object();
            auto responseCode = response.value("response_code").toInt();
            QString message = response.value("message").toString();
            replyData.append(QString::number(responseCode));
            replyData.append(message);
            return replyData;
        }
    }
}

QVector<QString> NetworkManager::getPublicIP()
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(LocalDB().getPublicIPURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QEventLoop eventLoop;
    auto reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    qDebug() << reply;

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty GetPublicIP Response");
            return replyData;
        }else{
            auto response = doc.object();
            QString ip = response.value("ip").toString();
            replyData.append("1");
            replyData.append(ip);
            return replyData;
        }
    }
}

QVector<QString> NetworkManager::getReferInfo()
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QString url = LocalDB().getReferRefreshURL()+"?username=HR4411-"+LocalDB::getUsername()+"&pass="+LocalDB::getPassword()+"&idReseller4=411";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QEventLoop eventLoop;
    auto reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty Refer Info Response");
            return replyData;
        }else{
            auto response = doc.object();
            if(response.contains("response_code")){
                replyData.append("2");
                replyData.append(response.value("message").toString());
                return replyData;
            }else{
                QJsonObject referData = response.value("referral_data").toObject();
                QString referCode = referData.value("referral_code").toString();
                QString usedReferCode = referData.value("used_referral_code").toString();
                QString availableBalance = QString::number(referData.value("available_balance").toInt());
                QString matureBalance = QString::number(referData.value("mature_balance").toInt());
                QString minWithdrawAmount = QString::number(referData.value("minimum_withdrawal_amount").toInt());
                QString pendingWithdrawRequest = QString::number(referData.value("pending_withdraw_request").toBool());
                QString eliligbleForUseReferCode = QString::number(referData.value("eliligbleForUseReferCode").toBool());
                replyData.append("1");
                replyData.append(referCode);
                replyData.append(usedReferCode);
                replyData.append(availableBalance);
                replyData.append(matureBalance);
                replyData.append(minWithdrawAmount);
                replyData.append(pendingWithdrawRequest);
                replyData.append(eliligbleForUseReferCode);
                return replyData;
            }
        }
    }
}

QVector<QString> NetworkManager::callReferRedeemAPI(QString redeemCode)
{
    QVector<QString> replyData;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrlQuery requestData;
    requestData.addQueryItem("username", "HR4411-"+LocalDB::getUsername());
    requestData.addQueryItem("referral_code", redeemCode);
    requestData.addQueryItem("udid", QSysInfo::machineUniqueId());
    requestData.addQueryItem("idReseller4", "411");
    QNetworkRequest request(LocalDB().getReferSubmitURL());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QEventLoop eventLoop;
    auto reply = manager->post(request, requestData.query(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error()) {
        qDebug() << reply->errorString();
        replyData.append("2");
        replyData.append(reply->errorString());
        return replyData;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if(doc.isNull() || !doc.isObject()){
            replyData.append("2");
            replyData.append("Empty Refer Submit Response");
            return replyData;
        }else{
            auto response = doc.object();
            auto responseCode = response.value("response_code").toInt();
            QString message = response.value("message").toString();
            replyData.append(QString::number(responseCode));
            replyData.append(message);
            return replyData;
        }
    }
}
