#ifndef CERT_H
#define CERT_H

#define TMP_CERT_PREFIX "tmp-certXXXXXX"

#include <QTemporaryFile>
extern "C" {
#include <gnutls/x509.h>
}

class Cert
{
public:
    Cert();
    ~Cert();

    /* functions return zero on success */
    int import_file(const QString& File);
    int import_pem(const QByteArray& data);
    void set(gnutls_x509_crt_t crt);
    int data_export(QByteArray& data);
    int tmpfile_export(QString& File);
    QString sha1_hash();
    bool is_url(const QString& str);

    bool is_ok() const;
    void clear();

    QString last_err;

private:
    gnutls_x509_crt_t crt;
    QTemporaryFile tmpfile;
    bool imported;
};

#endif // CERT_H
