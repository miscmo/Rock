#include "rock/tcp_server.h"
#include "rock/iomanager.h"
#include "rock/log.h"

rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

void run() {
    auto addr = rock::Address::LookupAny("0.0.0.0:8033");
    //auto addr2 = rock::UnixAddress::ptr(new rock::UnixAddress("/tmp/unix_addr"));
    std::vector<rock::Address::ptr> addrs;
    addrs.push_back(addr);
    //addrs.push_back(addr2);

    rock::TcpServer::ptr tcp_server(new rock::TcpServer);
    std::vector<rock::Address::ptr> fails;
    while(!tcp_server->bind(addrs, fails)) {
        sleep(2);
    }
    tcp_server->start();
    
}
int main(int argc, char** argv) {
    rock::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
