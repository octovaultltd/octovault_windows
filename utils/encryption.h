#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>

class Encryption
{
public:
    Encryption();
    static QString getBase64EncodedString(QString data);
    static QString getBase64DecodedString(QString data);
    static QString getEncryptedString(QString data, QString key);
    static QString getDecryptedString(QString data, QString key);
};

#endif // ENCRYPTION_H
