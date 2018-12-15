
#include "Configuration.h"

namespace APP_NAMESPACE {

Configuration::Configuration(const wxString& configFilename)
{
    config = new wxFileConfig(APP_NAME, APP_VENDOR, configFilename, APP_CONFIG_GLOBAL);
    wxConfigBase::Set(config);
}

Configuration::~Configuration()
{
    wxConfigBase::Set(NULL);
    // changes will be written back automatically
    // delete config;
}

bool Configuration::getString(const wxString& key, const wxString& defaultVal, wxString* result)
{
    return getString(APPSETTING_MAINGROUP, key, defaultVal, result);
}

bool Configuration::getString(const wxString& group, const wxString& key, const wxString& defaultVal, wxString* result)
{
    wxString realGroup = group;
    if (!realGroup.StartsWith("/"))
        realGroup = "/" + realGroup;
    config->SetPath(realGroup);
    bool bResult = config->Read(key, result, defaultVal);
    // reset path
    config->SetPath("");
    return bResult;
}


};  // namespace
