#include "my_module.h"
#include "rock/config.h"
#include "rock/log.h"

namespace name_space {

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

MyModule::MyModule()
    :rock::Module("project_name", "1.0", "") {
}

bool MyModule::onLoad() {
    ROCK_LOG_INFO(g_logger) << "onLoad";
    return true;
}

bool MyModule::onUnload() {
    ROCK_LOG_INFO(g_logger) << "onUnload";
    return true;
}

bool MyModule::onServerReady() {
    ROCK_LOG_INFO(g_logger) << "onServerReady";
    return true;
}

bool MyModule::onServerUp() {
    ROCK_LOG_INFO(g_logger) << "onServerUp";
    return true;
}

}

extern "C" {

rock::Module* CreateModule() {
    rock::Module* module = new name_space::MyModule;
    ROCK_LOG_INFO(name_space::g_logger) << "CreateModule " << module;
    return module;
}

void DestoryModule(rock::Module* module) {
    ROCK_LOG_INFO(name_space::g_logger) << "CreateModule " << module;
    delete module;
}

}
