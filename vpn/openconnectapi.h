#ifndef OPENCONNECTAPI_H
#define OPENCONNECTAPI_H

#ifdef _WIN32
#define DEFAULT_VPNC_SCRIPT "vpnc-script.js"
#else
#define DEFAULT_VPNC_SCRIPT "../Resources/vpnc-script"
#endif

#define OPAL_RECONNECT_INTERVAL 300
#include <fcntl.h>

#include <memory>

struct oc_auth_form;
struct oc_stats;

class OpenConnectConnection;

class OpenConnectApi
{
public:
    static int validate_peer_cert(void* privdata, const char* reason);
    static int process_auth_form(void* privdata, oc_auth_form* form);
    static void progress_vfn(void* privdata, int level, const char* fmt, ...);
    static int set_sock_block(int fd);
    static void stats_vfn(void* privdata, const oc_stats* stats);
    static void setupTunDevice(void* privdata);
    static void main_loop(OpenConnectConnection* vpninfo, void*);
};

#endif // OPENCONNECTAPI_H
