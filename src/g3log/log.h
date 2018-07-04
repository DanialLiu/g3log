#pragma once 

#include <memory>
#include "g3log.hpp"
#include "logworker.hpp"

// log module usage
// initilaze
//
// #include "base/log.h"
// int main()
// {
//     auto log = base::initLog("/tmp", argv[0]);
//     ......
// }
// 
// log file will save to /tmp/argv[0].xxxx.log


// print log
//
// #include "base/log.h"
//
// LOGI("tag") << "this is info";
// LOGV("tag") << "this is verbose";
// LOGD("tag") << "this is debug";
// LOGW("tag") << "this is warning";
// LOGE("tag") << "this is error";
// LOGDF("tag", "string format %2d", 1);
// LOGIF("tag", "string format %0.3f", 3.1419526);
//

// LOGI("tag") << "this is info" << ver << num;
// I表示日志的级别，总共6个
// V->VERBOSE   (无关紧要的啰嗦日志)
// D->DEBUG (调试用的日志)
// I->INFO      (一般日志，主业务相关的流程和变量等信息)
// W->WARNING   (警告，可以延后处理)
// E->ERROR (错误，需要立即处理)
// F->FATAL     (严重错误，立即结束进程并输出堆栈)
 
// tag用于区分日志所属功能模块
 
// 输出采用流式的方式
 
// 另外还提供了方便格式化字符串版本的日志输出，在以上6种宏后面加字母"F"即可
// LOGIF("tag", "string format %0.3f", 3.1419526);

namespace base
{
struct ColorLogSink {
    enum FG_Color {YELLOW = 33, RED = 31, GREEN=32, WHITE = 97, BLUE = 34};
    FG_Color GetColor(const LEVELS level) const;
    void ReceiveLogMessage(g3::LogMessageMover logEntry);
};
struct LogHolder
{
    std::unique_ptr<g3::LogWorker> worker;
    std::unique_ptr<g3::FileSinkHandle> handle;
    std::unique_ptr<g3::SinkHandle<ColorLogSink>> sinkHandle;
};
std::unique_ptr<LogHolder> initLog(const std::string& logpath, const std::string& logname);
}
