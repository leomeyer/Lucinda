#include "LuaIntegration.h"
namespace APP_NAMESPACE {

LuaIntegration::~LuaIntegration()
{
    //dtor
}

LuaIntegration::LuaIntegration(Context* context, LuaFunctions* functions)
{
    this->context = context;
}

void LuaIntegration::runFile(wxString filename)
{

}

};  // namespace
