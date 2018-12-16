#ifndef LOGGER_H
#define LOGGER_H

#include "GlobalDefines.h"

#include <wx/wx.h>

namespace APP_NAMESPACE {

class Configuration;

/** Thread-safe logger */
class Logger
{
    public:
        Logger(Configuration* config);
        virtual ~Logger();

        void logDebug(const wxString& msg);

        void logInfo(const wxString& msg);

        void logWarning(const wxString& msg);

        void logError(const wxString& msg);

    protected:

        Configuration* config;
        wxCriticalSection criticalSection;

        void logMessage(const wxString& msg);

    private:
};

}; // namespace

#endif // LOGGER_H
