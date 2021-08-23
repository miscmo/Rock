#include "ws_server.h"
#include "rock/log.h"

namespace rock {
namespace http {

static rock::Logger::ptr g_logger = ROCK_LOG_NAME("system");

WSServer::WSServer(rock::IOManager* worker, rock::IOManager* io_worker, rock::IOManager* accept_worker)
    :TcpServer(worker, io_worker, accept_worker) {
    m_dispatch.reset(new WSServletDispatch);
    m_type = "websocket_server";
}

void WSServer::handleClient(Socket::ptr client) {
    ROCK_LOG_DEBUG(g_logger) << "handleClient " << *client;
    WSSession::ptr session(new WSSession(client));
    do {
        HttpRequest::ptr header = session->handleShake();
        if(!header) {
            ROCK_LOG_DEBUG(g_logger) << "handleShake error";
            break;
        }
        WSServlet::ptr servlet = m_dispatch->getWSServlet(header->getPath());
        if(!servlet) {
            ROCK_LOG_DEBUG(g_logger) << "no match WSServlet";
            break;
        }
        int rt = servlet->onConnect(header, session);
        if(rt) {
            ROCK_LOG_DEBUG(g_logger) << "onConnect return " << rt;
            break;
        }
        while(true) {
            auto msg = session->recvMessage();
            if(!msg) {
                break;
            }
            rt = servlet->handle(header, msg, session);
            if(rt) {
                ROCK_LOG_DEBUG(g_logger) << "handle return " << rt;
                break;
            }
        }
        servlet->onClose(header, session);
    } while(0);
    session->close();
}

}
}
