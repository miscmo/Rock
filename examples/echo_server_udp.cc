#include "rock/socket.h"
#include "rock/log.h"
#include "rock/iomanager.h"

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

void run() {
    rock::IPAddress::ptr addr = rock::Address::LookupAnyIPAddress("0.0.0.0:8050");
    rock::Socket::ptr sock = rock::Socket::CreateUDP(addr);
    if(sock->bind(addr)) {
        ROCK_LOG_INFO(g_logger) << "udp bind : " << *addr;
    } else {
        ROCK_LOG_ERROR(g_logger) << "udp bind : " << *addr << " fail";
        return;
    }
    while(true) {
        char buff[1024];
        rock::Address::ptr from(new rock::IPv4Address);
        int len = sock->recvFrom(buff, 1024, from);
        if(len > 0) {
            buff[len] = '\0';
            ROCK_LOG_INFO(g_logger) << "recv: " << buff << " from: " << *from;
            len = sock->sendTo(buff, len, from);
            if(len < 0) {
                ROCK_LOG_INFO(g_logger) << "send: " << buff << " to: " << *from
                    << " error=" << len;
            }
        }
    }
}

int main(int argc, char** argv) {
    rock::IOManager iom(1);
    iom.schedule(run);
    return 0;
}
