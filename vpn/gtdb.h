#ifndef GTDB_H
#define GTDB_H

#include <memory>

extern "C" {
#include <gnutls/gnutls.h>
}

class OpenConnectServer;

class gtdb
{
public:
    gtdb(std::shared_ptr<OpenConnectServer> s);
    ~gtdb();

    gnutls_tdb_t get_tdb() const;

    std::shared_ptr<OpenConnectServer> server;
    gnutls_tdb_t tdb;
};

#endif // GTDB_H
