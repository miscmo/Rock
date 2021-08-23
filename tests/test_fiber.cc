#include "rock/rock.h"

rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

void run_in_fiber() {
    ROCK_LOG_INFO(g_logger) << "run_in_fiber begin";
    rock::Fiber::YieldToHold();
    ROCK_LOG_INFO(g_logger) << "run_in_fiber end";
    rock::Fiber::YieldToHold();
}

void test_fiber() {
    ROCK_LOG_INFO(g_logger) << "main begin -1";
    {
        rock::Fiber::GetThis();
        ROCK_LOG_INFO(g_logger) << "main begin";
        rock::Fiber::ptr fiber(new rock::Fiber(run_in_fiber));
        fiber->swapIn();
        ROCK_LOG_INFO(g_logger) << "main after swapIn";
        fiber->swapIn();
        ROCK_LOG_INFO(g_logger) << "main after end";
        fiber->swapIn();
    }
    ROCK_LOG_INFO(g_logger) << "main after end2";
}

int main(int argc, char** argv) {
    rock::Thread::SetName("main");

    std::vector<rock::Thread::ptr> thrs;
    for(int i = 0; i < 3; ++i) {
        thrs.push_back(rock::Thread::ptr(
                    new rock::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    for(auto i : thrs) {
        i->join();
    }
    return 0;
}
