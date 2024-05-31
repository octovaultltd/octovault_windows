#ifndef OPENCONNECTINTERFACE_H
#define OPENCONNECTINTERFACE_H

#define INVALID_SOCKET -1
#define ms_sleep(x) usleep(1000 * x)
#ifdef _WIN32
#define pipe_write(x, y, z) send(x, y, z, 0)
#else
#define pipe_write(x, y, z) write(x, y, z)
#endif
#define OPAL_DTLS_TIMEOUT 25

#include <QFutureWatcher>
#ifdef _WIN32
#include <winsock.h>
#else
#define SOCKET int
#endif
#include "openconnectapi.h"
#include "openconnectserver.h"
#include <memory>

struct openconnect_info;

class OpenConnectConnection : public QObject
{
    Q_OBJECT
public:
    enum Status {
        IDLE = 0,
        CONNECTING = 1,
        CONNECTED = 2,
        IDLING = 3
    };

    enum ConnectionError {
        NONE = 0,
        SOCKET_ACTIVE = 1,
        INSTANCE_ACTIVE,
        CREDENTIAL_INVALID,
        SERVER_INVALID,
        VPN_INIT_FAILED,
        VPN_IPC_ERROR
    };

public:
    OpenConnectConnection();
    ~OpenConnectConnection();

    void init();
    void release();

    std::shared_ptr<OpenConnectServer> server() const;
    void setServer(std::shared_ptr<OpenConnectServer> server);

    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

    ConnectionError connect();
    void disconnect();

    Status status() const;
    void setStatus(const Status &status);
    void onStatusChanged(Status status);

    int ctspConnect();
    int dtls_connect();
    void fetchInfo();
    void fetchCipherInfo();

    QString lastError() const;
    void setLastError(const QString &lastError);

    void setStats(uint64_t tx, uint64_t rx);

    void logOpenConnect();

    int requestStats();

    void setType(const int type);

    void setOpenConfig(const QString config, const QString address);

signals:
    void statusChanged(Status status); // Emitted from thread. Connect async
    void statsChanged(uint64_t tx, uint64_t rx); // Emitted from thread. Connect async

private:
    QString m_username, m_password;
    std::shared_ptr<OpenConnectServer> m_server;
    SOCKET cmd_fd;
    QFutureWatcher<void> futureWatcher;
    Status m_status;
    QString m_lastError;
    QString open_config;
    int m_server_type;

    // Stats
    QString m_dns, m_ip, m_ip6, m_cstp, m_dtls;

    //Openconnect api
    openconnect_info* vpninfo;
    unsigned int authgroup_set;
    unsigned int password_set;
    unsigned int form_attempt;
    unsigned int form_pass_attempt;

    friend OpenConnectApi;
};

#endif // OPENCONNECTINTERFACE_H
