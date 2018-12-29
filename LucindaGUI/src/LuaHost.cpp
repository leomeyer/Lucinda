#include "LuaHost.h"

#include <memory>

extern "C" {
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

namespace APP_NAMESPACE {

LuaHost::LuaHost()
{
    state = nullptr;
}

LuaHost::~LuaHost()
{
    if (state != nullptr)
        free(state);
}

int LuaHost::myLuaFunction(lua_State* L)
{

}

int LuaHost::myLuaFunctionCallback(lua_State* L)
{
    lua_getupvalue(L, lua_upvalueindex(1), 1); //pushes the light userdata
    LuaHost* obj = static_cast<LuaHost*>(lua_touserdata(L, -1)); //gets the value of the user data
    lua_pop(L, 1); //pop userdata
    obj->myLuaFunction(L); //call actual function
}

void LuaHost::runFile(wxString filename)
{
    state = luaL_newstate();
    luaL_openlibs(state);

    // register callback
    lua_pushlightuserdata(state, this);
    lua_pushcclosure(state, LuaHost::myLuaFunctionCallback, 1);
}

}; // namespace
