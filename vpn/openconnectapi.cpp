#include "openconnectapi.h"
#include "openconnectconnection.h"
#include "openconnectserver.h"
#include "gtdb.h"

#include <QCoreApplication>
#include <QDir>

extern "C" {
#include <gnutls/pkcs11.h>
#include <openconnect.h>
}

static int last_form_empty;

int OpenConnectApi::validate_peer_cert(void* privdata, const char* reason)
{
    Q_UNUSED(reason);
    OpenConnectConnection* vpn = static_cast<OpenConnectConnection*>(privdata);
    unsigned char* der = nullptr;

    int der_size = openconnect_get_peer_cert_DER(vpn->vpninfo, &der);
    if (der_size <= 0) {
        return -1;
    }

    const char* hash = openconnect_get_peer_cert_hash(vpn->vpninfo);
    if (hash == nullptr) {
        return -1;
    }

    gnutls_datum_t raw;
    raw.data = der;
    raw.size = static_cast<unsigned int>(der_size);

    gtdb tdb(vpn->server());
    int ret = gnutls_verify_stored_pubkey(reinterpret_cast<const char*>(&tdb),
                                          tdb.tdb, "", "", GNUTLS_CRT_X509, &raw, 0);

    char* details = openconnect_get_peer_cert_details(vpn->vpninfo);
    QString dstr;
    if (details != nullptr) {
        dstr = QString::fromUtf8(details);
        free(details);
    }

    bool save = false;
    if (ret == GNUTLS_E_NO_CERTIFICATE_FOUND) {
        // Auto insert new key
        save = true;
    } else if (ret == GNUTLS_E_CERTIFICATE_KEY_MISMATCH) {
        // Auto-update key if changed
        save = true;
    } else if (ret < 0) {
        QString str = QObject::tr("Could not verify certificate: ");
        str += gnutls_strerror(ret);
        return -1;
    }

    if (save != false) {
        ret = gnutls_store_pubkey(reinterpret_cast<const char*>(&tdb), tdb.tdb,
                                  "", "", GNUTLS_CRT_X509, &raw, 0, 0);
        if (ret < 0) {
            QString str = QObject::tr("Could not store certificate: ");
            str += gnutls_strerror(ret);
        } else {
            //            vpn->server()->save(); //TODO: Move to CONFIG
        }
    }
    return 0;
}

int OpenConnectApi::process_auth_form(void *privdata, oc_auth_form *form)
{
    OpenConnectConnection* vpn = static_cast<OpenConnectConnection*>(privdata);
    bool ok;
    QString text;
    struct oc_form_opt* opt;
    QStringList gitems;
    QStringList ditems;
    int i, idx;

    if (form->banner) {
    }

    if (form->message) {
    }

    if (form->error) {
    }

    int empty = 1;
    if (form->authgroup_opt) {
        struct oc_form_opt_select* select_opt = form->authgroup_opt;

        for (i = 0; i < select_opt->nr_choices; i++) {
            ditems << select_opt->choices[i]->label;
            gitems << select_opt->choices[i]->name;
        }

        if (select_opt->nr_choices == 1) {
            openconnect_set_option_value(&select_opt->form,
                                         select_opt->choices[0]->name);
        } else if (gitems.contains(vpn->server()->getGroupname())) {
            openconnect_set_option_value(&select_opt->form,
                                         vpn->server()->getGroupname().toLatin1().data());
        } else {
            // TODO: Input
            goto fail;
        }

        if (vpn->authgroup_set == 0) {
            vpn->authgroup_set = 1;
            return OC_FORM_RESULT_NEWGROUP;
        }
    }

    for (opt = form->opts; opt; opt = opt->next) {
        text.clear();
        if (opt->flags & OC_FORM_OPT_IGNORE)
            continue;

        if (opt->type == OC_FORM_OPT_SELECT) {
            QStringList items;
            struct oc_form_opt_select* select_opt = reinterpret_cast<oc_form_opt_select*>(opt);

            if (select_opt == form->authgroup_opt) {
                continue;
            }

            for (i = 0; i < select_opt->nr_choices; i++) {
                items << select_opt->choices[i]->label;
            }

            {
                ok = false; // TODO: Fix
            }

            if (!ok)
                goto fail;

            idx = ditems.indexOf(text);
            if (idx == -1)
                goto fail;

            openconnect_set_option_value(opt, select_opt->choices[idx]->name);
            empty = 0;
        } else if (opt->type == OC_FORM_OPT_TEXT) {

            if (vpn->form_attempt == 0
                && vpn->username().isEmpty() == false
                && strcasecmp(opt->name, "username") == 0) {
                openconnect_set_option_value(opt,
                                             vpn->username().toLatin1().data());
                empty = 0;
                continue;
            }

            goto fail;

        } else if (opt->type == OC_FORM_OPT_PASSWORD) {

            if (vpn->form_pass_attempt == 0
                && vpn->password().isEmpty() == false
                && strcasecmp(opt->name, "password") == 0) {
                openconnect_set_option_value(opt,
                                             vpn->password().toLatin1().data());
                empty = 0;
                continue;
            }

            goto fail;
        } else {
        }
    }

    /* prevent infinite loops if the authgroup requires certificate auth only */
    if (last_form_empty && empty) {
        return OC_FORM_RESULT_CANCELLED;
    }
    last_form_empty = empty;

    return OC_FORM_RESULT_OK;
fail:
    return OC_FORM_RESULT_CANCELLED;
}

void OpenConnectApi::progress_vfn(void* privdata, int level, const char* fmt, ...)
{
    Q_UNUSED(privdata);
    char buf[512];
    size_t len;
    va_list args;

    /* don't spam */
    if (level == PRG_TRACE)
        return;

    buf[0] = 0;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    len = strlen(buf);
    if (buf[len - 1] == '\n')
        buf[len - 1] = 0;
}

int OpenConnectApi::set_sock_block(int fd)
{
#ifdef _WIN32
    unsigned long mode = 0;
    return ioctlsocket(static_cast<SOCKET>(fd), static_cast<long>(FIONBIO), &mode);
#else
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) & ~O_NONBLOCK);
#endif
}

void OpenConnectApi::stats_vfn(void *privdata, const oc_stats *stats)
{
    OpenConnectConnection* vpn = static_cast<OpenConnectConnection*>(privdata);
    const char* cipher;
    QString dtls;

    cipher = openconnect_get_dtls_cipher(vpn->vpninfo);
    if (cipher != nullptr) {
        dtls = QLatin1String(cipher);
    }

     vpn->setStats(stats->tx_bytes, stats->rx_bytes);
}

void OpenConnectApi::setupTunDevice(void *privdata)
{
    OpenConnectConnection* vpn = static_cast<OpenConnectConnection*>(privdata);

    QByteArray vpncScriptFullPath;
    vpncScriptFullPath.append(QCoreApplication::applicationDirPath());
    vpncScriptFullPath.append(QDir::separator());
    vpncScriptFullPath.append(DEFAULT_VPNC_SCRIPT);

    int ret = openconnect_setup_tun_device(vpn->vpninfo, vpncScriptFullPath.constData(), nullptr);
    if (ret != 0) {
        vpn->setLastError(QObject::tr("Error setting up the TUN device"));
    }
    vpn->logOpenConnect();
}

void OpenConnectApi::main_loop(OpenConnectConnection *vpninfo, void *)
{
    emit vpninfo->statusChanged(OpenConnectConnection::CONNECTING);

    QString ip, ip6, dns, cstp, dtls;

    int ret = 0;
    ret = vpninfo->ctspConnect();
    if (ret != 0) {
        goto fail;
    }

    ret = vpninfo->dtls_connect();
    if (ret != 0) {
    }

    vpninfo->fetchInfo();
    vpninfo->fetchCipherInfo();
    emit vpninfo->statusChanged(OpenConnectConnection::CONNECTED);

    while (true) {
        int ret = openconnect_mainloop(vpninfo->vpninfo,
                                       OPAL_RECONNECT_INTERVAL,
                                       RECONNECT_INTERVAL_MIN);
        if (ret != 0) {
            vpninfo->setLastError(QObject::tr("Disconnected"));
            vpninfo->logOpenConnect();
            break;
        }
    }

fail: // LCA: drop this 'goto' and optimize values...
    emit vpninfo->statusChanged(OpenConnectConnection::IDLE);
}

