#include "rock/rock.h"
#include <unistd.h>

rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

int count = 0;
//rock::RWMutex s_mutex;
rock::Mutex s_mutex;

void fun1() {
    ROCK_LOG_INFO(g_logger) << "name: " << rock::Thread::GetName()
                             << " this.name: " << rock::Thread::GetThis()->getName()
                             << " id: " << rock::GetThreadId()
                             << " this.id: " << rock::Thread::GetThis()->getId();

    for(int i = 0; i < 100000; ++i) {
        //rock::RWMutex::WriteLock lock(s_mutex);
        rock::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void fun2() {
    while(true) {
        ROCK_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void fun3() {
    while(true) {
        ROCK_LOG_INFO(g_logger) << "========================================";
    }
}

int main(int argc, char** argv) {
    ROCK_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("/home/rock/test/rock/bin/conf/log2.yml");
    rock::Config::LoadFromYaml(root);

    std::vector<rock::Thread::ptr> thrs;
    for(int i = 0; i < 1; ++i) {
        rock::Thread::ptr thr(new rock::Thread(&fun2, "name_" + std::to_string(i * 2)));
        //rock::Thread::ptr thr2(new rock::Thread(&fun3, "name_" + std::to_string(i * 2 + 1)));
        thrs.push_back(thr);
        //thrs.push_back(thr2);
    }

    for(size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }
    ROCK_LOG_INFO(g_logger) << "thread test end";
    ROCK_LOG_INFO(g_logger) << "count=" << count;

    return 0;
}
