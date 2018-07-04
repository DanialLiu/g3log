#include "g3log/log.h"
#include <iostream>
namespace base
{

ColorLogSink::FG_Color ColorLogSink::GetColor(const LEVELS level) const 
{
    if (level.value == INFO.value) { return BLUE; }
    if (level.value == WARNING.value) { return YELLOW; }
    if (level.value == DEBUG.value) { return GREEN; }
    if (level.value == ERROR.value || g3::internal::wasFatal(level)) { return RED; }
    return WHITE;
}
void ColorLogSink::ReceiveLogMessage(g3::LogMessageMover logEntry)
{
    auto level = logEntry.get()._level;
    auto color = GetColor(level);
    std::cout << "\033[" << color << "m" << logEntry.get().toString() << "\033[m";
}
std::unique_ptr<LogHolder> initLog(const std::string& logpath, const std::string& logname)
{
	auto log = std::make_unique<LogHolder>();
	log->worker = g3::LogWorker::createLogWorker();
	log->handle= log->worker->addDefaultLogger(logname, logpath);
	log->sinkHandle = log->worker->addSink(std::make_unique<ColorLogSink>(),
	                         &ColorLogSink::ReceiveLogMessage);
	g3::initializeLogging(log->worker.get());
	return log;
}
	
}
