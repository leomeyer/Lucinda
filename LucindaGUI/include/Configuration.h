#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "GlobalDefines.h"

#include <wx/fileconf.h>

namespace APP_NAMESPACE {

class Configuration
{
    public:
        Configuration(const wxString& configFilename);
        virtual ~Configuration();

        /** Reads a string from the main group (APPSETTING_MAINGROUP). */
        bool getString(const wxString& key, const wxString& defaultVal, wxString* result);

        /** Reads a string using the specified group. */
        bool getString(const wxString& group, const wxString& key, const wxString& defaultVal, wxString* result);

    protected:
        wxFileConfig* config;

    private:
};

};  // namespace

#endif // CONFIGURATION_H
