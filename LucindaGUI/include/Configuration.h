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

        const wxString& getOrigin();

        /** Reads a string from the main group (APPSETTING_MAINGROUP). */
        bool getString(const wxString& key, const wxString& defaultVal, wxString* result);

        /** Reads a string using the specified group. */
        bool getString(const wxString& group, const wxString& key, const wxString& defaultVal, wxString* result);

        /** Reads a long from the main group (APPSETTING_MAINGROUP). */
        long getLong(const wxString& key, const long defaultVal);

        /** Reads a long using the specified group. */
        long getLong(const wxString& group, const wxString& key, const long defaultVal);

        void setString(const wxString& group, const wxString& key, const wxString& value);

    protected:
        wxFileConfig* config;
        wxString origin;

    private:
};

};  // namespace

#endif // CONFIGURATION_H
