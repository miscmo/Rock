#include "rock/daemon.h"
#include "rock/iomanager.h"
#include "rock/log.h"

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

rock::Timer::ptr timer;
int server_main(int argc, char** argv) {
    ROCK_LOG_INFO(g_logger) << rock::ProcessInfoMgr::GetInstance()->toString();
    rock::IOManager iom(1);
    timer = iom.addTimer(1000, [](){
            ROCK_LOG_INFO(g_logger) << "onTimer";
            static int count = 0;
            if(++count > 10) {
                exit(1);
            }
    }, true);
    return 0;
}

int main(int argc, char** argv) {
    return rock::start_daemon(argc, argv, server_main, argc != 1);
}
