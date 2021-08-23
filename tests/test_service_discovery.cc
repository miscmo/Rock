#include "rock/streams/service_discovery.h"
#include "rock/iomanager.h"
#include "rock/rock/rock_stream.h"
#include "rock/log.h"
#include "rock/worker.h"

rock::ZKServiceDiscovery::ptr zksd(new rock::ZKServiceDiscovery("127.0.0.1:21812"));
rock::RockSDLoadBalance::ptr rsdlb(new rock::RockSDLoadBalance(zksd));

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

std::atomic<uint32_t> s_id;
void on_timer() {
    g_logger->setLevel(rock::LogLevel::INFO);
    //ROCK_LOG_INFO(g_logger) << "on_timer";
    rock::RockRequest::ptr req(new rock::RockRequest);
    req->setSn(++s_id);
    req->setCmd(100);
    req->setBody("hello");

    auto rt = rsdlb->request("rock.top", "blog", req, 1000);
    if(!rt->response) {
        if(req->getSn() % 50 == 0) {
            ROCK_LOG_ERROR(g_logger) << "invalid response: " << rt->toString();
        }
    } else {
        if(req->getSn() % 1000 == 0) {
            ROCK_LOG_INFO(g_logger) << rt->toString();
        }
    }
}

void run() {
    zksd->setSelfInfo("127.0.0.1:2222");
    zksd->setSelfData("aaaa");

    std::unordered_map<std::string, std::unordered_map<std::string,std::string> > confs;
    confs["rock.top"]["blog"] = "fair";
    rsdlb->start(confs);
    //ROCK_LOG_INFO(g_logger) << "on_timer---";

    rock::IOManager::GetThis()->addTimer(1, on_timer, true);
}

int main(int argc, char** argv) {
    rock::WorkerMgr::GetInstance()->init({
        {"service_io", {
            {"thread_num", "1"}
        }}
    });
    rock::IOManager iom(1);
    iom.addTimer(1000, [](){
            std::cout << rsdlb->statusString() << std::endl;
    }, true);
    iom.schedule(run);
    return 0;
}
