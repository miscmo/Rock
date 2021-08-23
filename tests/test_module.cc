#include "rock/module.h"
#include "rock/singleton.h"
#include <iostream>
#include "rock/log.h"
#include "rock/db/redis.h"

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

class A {
public:
    A() {
        std::cout << "A::A " << this << std::endl;
    }

    ~A() {
        std::cout << "A::~A " << this << std::endl;
    }

};

class MyModule : public rock::RockModule {
public:
    MyModule()
        :RockModule("hello", "1.0", "") {
        //rock::Singleton<A>::GetInstance();
    }

    bool onLoad() override {
        rock::Singleton<A>::GetInstance();
        std::cout << "-----------onLoad------------" << std::endl;
        return true;
    }

    bool onUnload() override {
        rock::Singleton<A>::GetInstance();
        std::cout << "-----------onUnload------------" << std::endl;
        return true;
    }

    bool onServerReady() {
        registerService("rock", "rock.top", "blog");
        auto rpy = rock::RedisUtil::Cmd("local", "get abc");
        if(!rpy) {
            ROCK_LOG_ERROR(g_logger) << "redis cmd get abc error";
        } else {
            ROCK_LOG_ERROR(g_logger) << "redis get abc: "
                << (rpy->str ? rpy->str : "(null)");
        }
        return true;
    }

    bool handleRockRequest(rock::RockRequest::ptr request
                        ,rock::RockResponse::ptr response
                        ,rock::RockStream::ptr stream) {
        //ROCK_LOG_INFO(g_logger) << "handleRockRequest " << request->toString();
        //sleep(1);
        response->setResult(0);
        response->setResultStr("ok");
        response->setBody("echo: " + request->getBody());

        usleep(100 * 1000);
        auto addr = stream->getLocalAddressString();
        if(addr.find("8061") != std::string::npos) {
            if(rand() % 100 < 50) {
                usleep(10 * 1000);
            } else if(rand() % 100 < 10) {
                response->setResult(-1000);
            }
        } else {
            //if(rand() % 100 < 25) {
            //    usleep(10 * 1000);
            //} else if(rand() % 100 < 10) {
            //    response->setResult(-1000);
            //}
        }
        return true;
        //return rand() % 100 < 90;
    }

    bool handleRockNotify(rock::RockNotify::ptr notify 
                        ,rock::RockStream::ptr stream) {
        ROCK_LOG_INFO(g_logger) << "handleRockNotify " << notify->toString();
        return true;
    }

};

extern "C" {

rock::Module* CreateModule() {
    rock::Singleton<A>::GetInstance();
    std::cout << "=============CreateModule=================" << std::endl;
    return new MyModule;
}

void DestoryModule(rock::Module* ptr) {
    std::cout << "=============DestoryModule=================" << std::endl;
    delete ptr;
}

}
