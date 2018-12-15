#include "Context.h"

namespace APP_NAMESPACE {

Context::Context()
{
    //ctor
}

Context::~Context()
{
    // saves settings automatically
    delete config;
}

void Context::initialize(const wxString& configFileName)
{
    config = new Configuration(configFileName);
}

};  // namespace
