#include "rock/rock.h"
#include "rock/rock/rock_stream.h"

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

rock::RockConnection::ptr conn(new rock::RockConnection);
void run() {
    conn->setAutoConnect(true);
    rock::Address::ptr addr = rock::Address::LookupAny("127.0.0.1:8061");
    if(!conn->connect(addr)) {
        ROCK_LOG_INFO(g_logger) << "connect " << *addr << " false";
    }
    conn->start();

    rock::IOManager::GetThis()->addTimer(1000, [](){
        rock::RockRequest::ptr req(new rock::RockRequest);
        static uint32_t s_sn = 0;
        req->setSn(++s_sn);
        req->setCmd(100);
        req->setBody("hello world sn=" + std::to_string(s_sn));

        auto rsp = conn->request(req, 300);
        if(rsp->response) {
            ROCK_LOG_INFO(g_logger) << rsp->response->toString();
        } else {
            ROCK_LOG_INFO(g_logger) << "error result=" << rsp->result;
        }
    }, true);
}

int main(int argc, char** argv) {
    rock::IOManager iom(1);
    iom.schedule(run);
    return 0;
}
