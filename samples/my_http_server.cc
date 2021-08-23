#include "rock/http/http_server.h"
#include "rock/log.h"

rock::Logger::ptr g_logger = ROCK_LOG_ROOT();
rock::IOManager::ptr worker;
void run() {
    g_logger->setLevel(rock::LogLevel::INFO);
    rock::Address::ptr addr = rock::Address::LookupAnyIPAddress("0.0.0.0:8020");
    if(!addr) {
        ROCK_LOG_ERROR(g_logger) << "get address error";
        return;
    }

    //true 支持长连接
    rock::http::HttpServer::ptr http_server(new rock::http::HttpServer(true, worker.get()));
    //rock::http::HttpServer::ptr http_server(new rock::http::HttpServer(true));
    bool ssl = false;
    while(!http_server->bind(addr, ssl)) {
        ROCK_LOG_ERROR(g_logger) << "bind " << *addr << " fail";
        sleep(1);
    }

    if(ssl) {
        //http_server->loadCertificates("/home/apps/soft/rock/keys/server.crt", "/home/apps/soft/rock/keys/server.key");
    }

    http_server->start();
}

int main(int argc, char** argv) {
    rock::IOManager iom(1);
    //worker.reset(new rock::IOManager(4, false));
    worker.reset(new rock::IOManager(1, false));
    iom.schedule(run);
    return 0;
}
