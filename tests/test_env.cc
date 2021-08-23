#include "rock/env.h"
#include <unistd.h>
#include <iostream>
#include <fstream>

struct A {
    A() {
        std::ifstream ifs("/proc/" + std::to_string(getpid()) + "/cmdline", std::ios::binary);
        std::string content;
        content.resize(4096);

        ifs.read(&content[0], content.size());
        content.resize(ifs.gcount());

        for(size_t i = 0; i < content.size(); ++i) {
            std::cout << i << " - " << content[i] << " - " << (int)content[i] << std::endl;
        }
    }
};

A a;

int main(int argc, char** argv) {
    std::cout << "argc=" << argc << std::endl;
    rock::EnvMgr::GetInstance()->addHelp("s", "start with the terminal");
    rock::EnvMgr::GetInstance()->addHelp("d", "run as daemon");
    rock::EnvMgr::GetInstance()->addHelp("p", "print help");
    if(!rock::EnvMgr::GetInstance()->init(argc, argv)) {
        rock::EnvMgr::GetInstance()->printHelp();
        return 0;
    }

    std::cout << "exe=" << rock::EnvMgr::GetInstance()->getExe() << std::endl;
    std::cout << "cwd=" << rock::EnvMgr::GetInstance()->getCwd() << std::endl;

    std::cout << "path=" << rock::EnvMgr::GetInstance()->getEnv("PATH", "xxx") << std::endl;
    std::cout << "test=" << rock::EnvMgr::GetInstance()->getEnv("TEST", "") << std::endl;
    std::cout << "set env " << rock::EnvMgr::GetInstance()->setEnv("TEST", "yy") << std::endl;
    std::cout << "test=" << rock::EnvMgr::GetInstance()->getEnv("TEST", "") << std::endl;
    if(rock::EnvMgr::GetInstance()->has("p")) {
        rock::EnvMgr::GetInstance()->printHelp();
    }
    return 0;
}
