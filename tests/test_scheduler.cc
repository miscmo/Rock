#include "rock/rock.h"

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

void test_fiber() {
    static int s_count = 5;
    ROCK_LOG_INFO(g_logger) << "test in fiber s_count=" << s_count;

    sleep(1);
    if(--s_count >= 0) {
        rock::Scheduler::GetThis()->schedule(&test_fiber, rock::GetThreadId());
    }
}

int main(int argc, char** argv) {
    ROCK_LOG_INFO(g_logger) << "main";
    rock::Scheduler sc(3, false, "test");
    sc.start();
    sleep(2);
    ROCK_LOG_INFO(g_logger) << "schedule";
    sc.schedule(&test_fiber);
    sc.stop();
    ROCK_LOG_INFO(g_logger) << "over";
    return 0;
}
