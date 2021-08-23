#ifndef __ROCK_ROCK_SERVER_H__
#define __ROCK_ROCK_SERVER_H__

#include "rock/rock/rock_stream.h"
#include "rock/tcp_server.h"

namespace rock {

class RockServer : public TcpServer {
public:
    typedef std::shared_ptr<RockServer> ptr;
    RockServer(const std::string& type = "rock"
               ,rock::IOManager* worker = rock::IOManager::GetThis()
               ,rock::IOManager* io_worker = rock::IOManager::GetThis()
               ,rock::IOManager* accept_worker = rock::IOManager::GetThis());

protected:
    virtual void handleClient(Socket::ptr client) override;
};

}

#endif
