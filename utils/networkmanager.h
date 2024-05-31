#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QString>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "utils/localdb.h"
#include "utils/commondata.h"
#include "utils/encryption.h"

class NetworkManager
{
public:
    NetworkManager();
    static QString getFirestoreData();
    static QVector<QString> callResetTokenVerifyAPI(QString username);
    static QVector<QString> callResetAPI(QString username, QString token, QString password, QString password_confirmation);
    static QVector<QString> callLoginAPI(QString username, QString password);
    static QVector<QString> callSignUpAPI(QString username, QString password);
    static QVector<QString> callTokenVerifyAPI(QString username, QString token, QString type);
    static QVector<QString> callForgetAPI(QString email);
    static QVector<QString> callDeviceInfoAPI();
    static QVector<QString> callDeleteAccountAPI();
    static QVector<QString> getPublicIP();
    static QVector<QString> getReferInfo();
    static QVector<QString> callResendTokenAPI(QString username);
    static QVector<QString> callReferRedeemAPI(QString redeemCode);
};

#endif // NETWORKMANAGER_H
