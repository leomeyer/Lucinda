#include "Context.h"

#include "Configuration.h"
#include "Logger.h"

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
}

void Context::initialize(const wxString& configFileName)
{
    config = new Configuration(configFileName);
    logger = new Logger(config);
}

};  // namespace
