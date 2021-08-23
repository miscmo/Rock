#include "rock/http/ws_server.h"
#include "rock/log.h"

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

void run() {
    rock::http::WSServer::ptr server(new rock::http::WSServer);
    rock::Address::ptr addr = rock::Address::LookupAnyIPAddress("0.0.0.0:8020");
    if(!addr) {
        ROCK_LOG_ERROR(g_logger) << "get address error";
        return;
    }
    auto fun = [](rock::http::HttpRequest::ptr header
                  ,rock::http::WSFrameMessage::ptr msg
                  ,rock::http::WSSession::ptr session) {
        session->sendMessage(msg);
        return 0;
    };

    server->getWSServletDispatch()->addServlet("/rock", fun);
    while(!server->bind(addr)) {
        ROCK_LOG_ERROR(g_logger) << "bind " << *addr << " fail";
        sleep(1);
    }
    server->start();
}

int main(int argc, char** argv) {
    rock::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
