#ifndef KEY_H
#define KEY_H

#define TMP_KEY_PREFIX "tmp-keyXXXXXX"

#include <QByteArray>
#include <QString>
#include <QTemporaryFile>
extern "C" {
#include <gnutls/x509.h>
}

class Key
{
public:
    Key();
    ~Key();

    /* functions return zero on success */
    int import_file(const QString& File);
    int import_pem(const QByteArray& data);
    void set(const gnutls_x509_privkey_t privkey);
    bool is_url(const QString& str);

    void set_window(QWidget* w);

    int data_export(QByteArray& data);
    int tmpfile_export(QString& File);

    bool is_ok() const;
    void get_url(QString& url) const;

    void clear();

    QString last_err;

private:
    gnutls_x509_privkey_t privkey;
    QTemporaryFile tmpfile;
    QString url;
    QWidget* w;
    bool imported;
};

#endif // KEY_H
