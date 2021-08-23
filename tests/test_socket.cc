#include "rock/socket.h"
#include "rock/rock.h"
#include "rock/iomanager.h"

static rock::Logger::ptr g_looger = ROCK_LOG_ROOT();

void test_socket() {
    //std::vector<rock::Address::ptr> addrs;
    //rock::Address::Lookup(addrs, "www.baidu.com", AF_INET);
    //rock::IPAddress::ptr addr;
    //for(auto& i : addrs) {
    //    ROCK_LOG_INFO(g_looger) << i->toString();
    //    addr = std::dynamic_pointer_cast<rock::IPAddress>(i);
    //    if(addr) {
    //        break;
    //    }
    //}
    rock::IPAddress::ptr addr = rock::Address::LookupAnyIPAddress("www.baidu.com");
    if(addr) {
        ROCK_LOG_INFO(g_looger) << "get address: " << addr->toString();
    } else {
        ROCK_LOG_ERROR(g_looger) << "get address fail";
        return;
    }

    rock::Socket::ptr sock = rock::Socket::CreateTCP(addr);
    addr->setPort(80);
    ROCK_LOG_INFO(g_looger) << "addr=" << addr->toString();
    if(!sock->connect(addr)) {
        ROCK_LOG_ERROR(g_looger) << "connect " << addr->toString() << " fail";
        return;
    } else {
        ROCK_LOG_INFO(g_looger) << "connect " << addr->toString() << " connected";
    }

    const char buff[] = "GET / HTTP/1.0\r\n\r\n";
    int rt = sock->send(buff, sizeof(buff));
    if(rt <= 0) {
        ROCK_LOG_INFO(g_looger) << "send fail rt=" << rt;
        return;
    }

    std::string buffs;
    buffs.resize(4096);
    rt = sock->recv(&buffs[0], buffs.size());

    if(rt <= 0) {
        ROCK_LOG_INFO(g_looger) << "recv fail rt=" << rt;
        return;
    }

    buffs.resize(rt);
    ROCK_LOG_INFO(g_looger) << buffs;
}

void test2() {
    rock::IPAddress::ptr addr = rock::Address::LookupAnyIPAddress("www.baidu.com:80");
    if(addr) {
        ROCK_LOG_INFO(g_looger) << "get address: " << addr->toString();
    } else {
        ROCK_LOG_ERROR(g_looger) << "get address fail";
        return;
    }

    rock::Socket::ptr sock = rock::Socket::CreateTCP(addr);
    if(!sock->connect(addr)) {
        ROCK_LOG_ERROR(g_looger) << "connect " << addr->toString() << " fail";
        return;
    } else {
        ROCK_LOG_INFO(g_looger) << "connect " << addr->toString() << " connected";
    }

    uint64_t ts = rock::GetCurrentUS();
    for(size_t i = 0; i < 10000000000ul; ++i) {
        if(int err = sock->getError()) {
            ROCK_LOG_INFO(g_looger) << "err=" << err << " errstr=" << strerror(err);
            break;
        }

        //struct tcp_info tcp_info;
        //if(!sock->getOption(IPPROTO_TCP, TCP_INFO, tcp_info)) {
        //    ROCK_LOG_INFO(g_looger) << "err";
        //    break;
        //}
        //if(tcp_info.tcpi_state != TCP_ESTABLISHED) {
        //    ROCK_LOG_INFO(g_looger)
        //            << " state=" << (int)tcp_info.tcpi_state;
        //    break;
        //}
        static int batch = 10000000;
        if(i && (i % batch) == 0) {
            uint64_t ts2 = rock::GetCurrentUS();
            ROCK_LOG_INFO(g_looger) << "i=" << i << " used: " << ((ts2 - ts) * 1.0 / batch) << " us";
            ts = ts2;
        }
    }
}

int main(int argc, char** argv) {
    rock::IOManager iom;
    iom.schedule(&test_socket);
    //iom.schedule(&test2);
    return 0;
}
