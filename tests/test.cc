#include <iostream>
#include "rock/log.h"
#include "rock/util.h"

int main(int argc, char** argv) {
    rock::Logger::ptr logger(new rock::Logger);
    logger->addAppender(rock::LogAppender::ptr(new rock::StdoutLogAppender));

    rock::FileLogAppender::ptr file_appender(new rock::FileLogAppender("./log.txt"));
    rock::LogFormatter::ptr fmt(new rock::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(rock::LogLevel::ERROR);

    logger->addAppender(file_appender);

    //rock::LogEvent::ptr event(new rock::LogEvent(__FILE__, __LINE__, 0, rock::GetThreadId(), rock::GetFiberId(), time(0)));
    //event->getSS() << "hello rock log";
    //logger->log(rock::LogLevel::DEBUG, event);
    std::cout << "hello rock log" << std::endl;

    ROCK_LOG_INFO(logger) << "test macro";
    ROCK_LOG_ERROR(logger) << "test macro error";

    ROCK_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

    auto l = rock::LoggerMgr::GetInstance()->getLogger("xx");
    ROCK_LOG_INFO(l) << "xxx";
    return 0;
}
