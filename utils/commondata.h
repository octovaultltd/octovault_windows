#ifndef COMMONDATA_H
#define COMMONDATA_H

#include <QString>
#include <QPair>
#include <QDateTime>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QTimeZone>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "vpn/openconnectconnection.h"

class OpenConnectConnection;

class CommonData
{
public:
    CommonData();
    static QString getAppName();
    static QString getAppVersion();
    static QJsonObject getServerByIPID(int ipID);
    static QPair<QString,QString> getManufacturerAndModel();
    static QString getCurrentTimeZone();
    static int getCurrentCountryCallingCode();
    static QString getLoginDecryptionKey();
    static QString getFirestoreDecryptionKey();
    static QString getFireStoreEndpoint();
    static QString getFlagImage(int code);
    static std::shared_ptr<OpenConnectConnection> getVPNConnection();
};

#endif // COMMONDATA_H
