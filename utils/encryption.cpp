#include "encryption.h"

Encryption::Encryption()
{

}

QString Encryption::getBase64EncodedString(QString data)
{
    return data.toUtf8().toBase64();
}

QString Encryption::getBase64DecodedString(QString data)
{
    return QByteArray::fromBase64(data.toUtf8());
}

QString Encryption::getEncryptedString(QString data, QString key)
{
    QString encodedString;

    QString encryptedString;

    for(auto i = 0; i < data.length(); i++)
    {
        encryptedString.append(data.at(i).toLatin1() ^ key.at(i % key.length()).toLatin1());
    }

    encodedString = encryptedString.toUtf8().toBase64();

    return encodedString;
}

QString Encryption::getDecryptedString(QString data, QString key)
{
    auto decodedbytes = QByteArray::fromBase64(data.toLatin1());

    QString decryptedString;
    for(auto i = 0; i < decodedbytes.length(); i++)
    {
        decryptedString.append(decodedbytes.at(i) ^ key.at(i % key.length()).toLatin1());
    }

    return decryptedString;
}
