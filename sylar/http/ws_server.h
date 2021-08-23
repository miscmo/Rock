#ifndef __ROCK_HTTP_WS_SERVER_H__
#define __ROCK_HTTP_WS_SERVER_H__

#include "rock/tcp_server.h"
#include "ws_session.h"
#include "ws_servlet.h"

namespace rock {
namespace http {

class WSServer : public TcpServer {
public:
    typedef std::shared_ptr<WSServer> ptr;

    WSServer(rock::IOManager* worker = rock::IOManager::GetThis()
             , rock::IOManager* io_worker = rock::IOManager::GetThis()
             , rock::IOManager* accept_worker = rock::IOManager::GetThis());

    WSServletDispatch::ptr getWSServletDispatch() const { return m_dispatch;}
    void setWSServletDispatch(WSServletDispatch::ptr v) { m_dispatch = v;}
protected:
    virtual void handleClient(Socket::ptr client) override;
protected:
    WSServletDispatch::ptr m_dispatch;
};

}
}

#endif
