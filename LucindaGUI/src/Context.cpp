#include "Context.h"

#include "Configuration.h"
#include "Logger.h"
#include "ColorManagement.h"

namespace APP_NAMESPACE {

Context::Context()
{
    //ctor
}

Context::~Context()
{
    // saves settings automatically
    delete config;
    delete logger;
    delete colorManagement;
}

void Context::initialize(const wxString& configFileName)
{
    config = new Configuration(configFileName);
    logger = new Logger(config);
    colorManagement = new ColorManagement();
}

};  // namespace
