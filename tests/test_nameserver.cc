#include "rock/rock.h"
#include "rock/ns/ns_protocol.h"
#include "rock/ns/ns_client.h"

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

int type = 0;

void run() {
    g_logger->setLevel(rock::LogLevel::INFO);
    auto addr = rock::IPAddress::Create("127.0.0.1", 8072);
    //if(!conn->connect(addr)) {
    //    ROCK_LOG_ERROR(g_logger) << "connect to: " << *addr << " fail";
    //    return;
    //}
    if(type == 0) {
        for(int i = 0; i < 5000; ++i) {
            rock::RockConnection::ptr conn(new rock::RockConnection);
            conn->connect(addr);
            rock::IOManager::GetThis()->addTimer(3000, [conn, i](){
                    rock::RockRequest::ptr req(new rock::RockRequest);
                    req->setCmd((int)rock::ns::NSCommand::REGISTER);
                    auto rinfo = std::make_shared<rock::ns::RegisterRequest>();
                    auto info = rinfo->add_infos();
                    info->set_domain(std::to_string(rand() % 2) + "domain.com");
                    info->add_cmds(rand() % 2 + 100);
                    info->add_cmds(rand() % 2 + 200);
                    info->mutable_node()->set_ip("127.0.0.1");
                    info->mutable_node()->set_port(1000 + i);
                    info->mutable_node()->set_weight(100);
                    req->setAsPB(*rinfo);

                    auto rt = conn->request(req, 100);
                    ROCK_LOG_INFO(g_logger) << "[result="
                        << rt->result << " response="
                        << (rt->response ? rt->response->toString() : "null")
                        << "]";
            }, true);
            conn->start();
        }
    } else {
        for(int i = 0; i < 1000; ++i) {
            rock::ns::NSClient::ptr nsclient(new rock::ns::NSClient);
            nsclient->init();
            nsclient->addQueryDomain(std::to_string(i % 2) + "domain.com");
            nsclient->connect(addr);
            nsclient->start();
            ROCK_LOG_INFO(g_logger) << "NSClient start: i=" << i;

            if(i == 0) {
                //rock::IOManager::GetThis()->addTimer(1000, [nsclient](){
                //    auto domains = nsclient->getDomains();
                //    domains->dump(std::cout, "    ");
                //}, true);
            }
        }

        //conn->setConnectCb([](rock::AsyncSocketStream::ptr ss) {
        //    auto conn = std::dynamic_pointer_cast<rock::RockConnection>(ss);
        //    rock::RockRequest::ptr req(new rock::RockRequest);
        //    req->setCmd((int)rock::ns::NSCommand::QUERY);
        //    auto rinfo = std::make_shared<rock::ns::QueryRequest>();
        //    rinfo->add_domains("0domain.com");
        //    req->setAsPB(*rinfo);
        //    auto rt = conn->request(req, 1000);
        //    ROCK_LOG_INFO(g_logger) << "[result="
        //        << rt->result << " response="
        //        << (rt->response ? rt->response->toString() : "null")
        //        << "]";
        //    return true;
        //});

        //conn->setNotifyHandler([](rock::RockNotify::ptr nty,rock::RockStream::ptr stream){
        //        auto nm = nty->getAsPB<rock::ns::NotifyMessage>();
        //        if(!nm) {
        //            ROCK_LOG_ERROR(g_logger) << "invalid notify message";
        //            return true;
        //        }
        //        ROCK_LOG_INFO(g_logger) << rock::PBToJsonString(*nm);
        //        return true;
        //});
    }
}

int main(int argc, char** argv) {
    if(argc > 1) {
        type = 1;
    }
    rock::IOManager iom(5);
    iom.schedule(run);
    return 0;
}
