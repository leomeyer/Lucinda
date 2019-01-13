#include "LuaHost.h"

#include <memory>

// PONDER_TYPE(APP_NAMESPACE::LuaTestClass)

/*    ponder::Class::declare<APP_NAMESPACE::LuaTestClass>()
        .function("printDebug", &APP_NAMESPACE::LuaTestClass::printDebug)
        ;
*/

namespace APP_NAMESPACE {

LuaHost::LuaHost()
{
//    state = nullptr;

}

LuaHost::~LuaHost()
{
}


void LuaHost::runFile(wxString filename)
{
/*
    state = luaL_newstate();
    luaL_openlibs(state);

    // register callback
    lua_pushlightuserdata(state, this);
    lua_pushcclosure(state, LuaHost::myLuaFunctionCallback, 1);
*/
}

}; // namespace
