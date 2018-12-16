#ifndef LOGGER_H
#define LOGGER_H

#include "GlobalDefines.h"

#include <wx/wx.h>
#include <wx/datetime.h>

namespace APP_NAMESPACE {

class Configuration;

/** Thread-safe logger */
class Logger
{
    public:

        enum LogPriority {
            LOG_DEBUG,
            LOG_INFO,
            LOG_WARNING,
            LOG_ERROR
        };

        struct LogMessage {
            wxDateTime datetime;
            LogPriority priority;
            wxString text;
        };

        Logger(Configuration* config);
        virtual ~Logger();

        void logDebug(const wxString& msg);

        void logInfo(const wxString& msg);

        void logWarning(const wxString& msg);

        void logError(const wxString& msg);

        wxDateTime getMessages(const wxDateTime& since, wxVector<LogMessage>& list);
    protected:

        Configuration* config;
        wxCriticalSection criticalSection;
        wxVector<LogMessage> messages;

        void logMessage(const wxString& msg, LogPriority priority);

    private:
};

}; // namespace

#endif // LOGGER_H
