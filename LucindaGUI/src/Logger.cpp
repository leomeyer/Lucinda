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
    logMessage(wxString("DEBUG: ") + msg);
}

void Logger::logInfo(const wxString& msg)
{
    logMessage(wxString("INFO: ") + msg);
}

void Logger::logWarning(const wxString& msg)
{
    logMessage(wxString("WARNING: ") + msg);
}

void Logger::logError(const wxString& msg)
{
    logMessage(wxString("ERROR: ") + msg);
}

void Logger::logMessage(const wxString& msg)
{
    wxCriticalSectionLocker enter(criticalSection);

    OutputDebugStr(msg.c_str());
    std::cout << msg << std::endl;
    std::cout.flush();
}

}; // namespace
