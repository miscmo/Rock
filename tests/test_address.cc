#include "rock/address.h"
#include "rock/log.h"

rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

void test() {
    std::vector<rock::Address::ptr> addrs;

    ROCK_LOG_INFO(g_logger) << "begin";
    bool v = rock::Address::Lookup(addrs, "localhost:3080");
    //bool v = rock::Address::Lookup(addrs, "www.baidu.com", AF_INET);
    //bool v = rock::Address::Lookup(addrs, "www.rock.top", AF_INET);
    ROCK_LOG_INFO(g_logger) << "end";
    if(!v) {
        ROCK_LOG_ERROR(g_logger) << "lookup fail";
        return;
    }

    for(size_t i = 0; i < addrs.size(); ++i) {
        ROCK_LOG_INFO(g_logger) << i << " - " << addrs[i]->toString();
    }

    auto addr = rock::Address::LookupAny("localhost:4080");
    if(addr) {
        ROCK_LOG_INFO(g_logger) << *addr;
    } else {
        ROCK_LOG_ERROR(g_logger) << "error";
    }
}

void test_iface() {
    std::multimap<std::string, std::pair<rock::Address::ptr, uint32_t> > results;

    bool v = rock::Address::GetInterfaceAddresses(results);
    if(!v) {
        ROCK_LOG_ERROR(g_logger) << "GetInterfaceAddresses fail";
        return;
    }

    for(auto& i: results) {
        ROCK_LOG_INFO(g_logger) << i.first << " - " << i.second.first->toString() << " - "
            << i.second.second;
    }
}

void test_ipv4() {
    //auto addr = rock::IPAddress::Create("www.rock.top");
    auto addr = rock::IPAddress::Create("127.0.0.8");
    if(addr) {
        ROCK_LOG_INFO(g_logger) << addr->toString();
    }
}

int main(int argc, char** argv) {
    //test_ipv4();
    //test_iface();
    test();
    return 0;
}
