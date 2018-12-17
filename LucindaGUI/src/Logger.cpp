#include "Logger.h"

#include "Configuration.h"

namespace APP_NAMESPACE {

Logger::Logger(Configuration* config)
{
    this->config = config;
}

Logger::~Logger()
{
    //dtor
}

void Logger::logDebug(const wxString& msg)
{
    logMessage(msg, LOG_DEBUG);
}

void Logger::logInfo(const wxString& msg)
{
    logMessage(msg, LOG_INFO);
}

void Logger::logWarning(const wxString& msg)
{
    logMessage(msg, LOG_WARNING);
}

void Logger::logError(const wxString& msg)
{
    logMessage(msg, LOG_ERROR);
}

void Logger::logMessage(const wxString& msg, LogPriority priority)
{
    wxCriticalSectionLocker enter(criticalSection);

    // store message
    LogMessage message;
    message.datetime = wxDateTime::UNow();
    message.priority = priority;
    message.text = msg;
    messages.push_back(message);

    OutputDebugStr(msg.c_str());
    std::cout << msg << std::endl;
    std::cout.flush();
}

wxDateTime Logger::getMessages(const wxDateTime& since, wxVector<LogMessage>& list) {
    wxCriticalSectionLocker enter(criticalSection);

    // return all messages since the given time in reverse order (most recent first)
    list.clear();
    auto begin = messages.begin();
    auto iter = messages.end() - 1;
    // start at the end
    while (iter != begin) {
        if ((*iter).datetime.IsEarlierThan(since))
            break;
        LogMessage copy = *iter;
        list.push_back(copy);
        --iter;
    }

    return wxDateTime::UNow();
}

}; // namespace
