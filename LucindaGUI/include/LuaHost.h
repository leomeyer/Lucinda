#ifndef LUAHOST_H
#define LUAHOST_H

#include "GlobalDefines.h"
#include "Context.h"
#include "Logger.h"
/*
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define PONDER_USES_LUA_IMPL
#define PONDER_USES_RUNTIME_IMPL
#include <ponder/class.hpp>
#include <ponder/classbuilder.hpp>
#include <ponder/uses/lua.hpp>

// required for Ponder
static_assert(LUA_VERSION_NUM==503, "Expecting Lua 5.3");
*/
#include <wx/wx.h>

namespace APP_NAMESPACE {

class LuaHost
{
    public:
        LuaHost();
        virtual ~LuaHost();
        // throws std::exceptions if something goes wrong
        void runFile(wxString filename);

    protected:
//        lua_State* state;

    private:
};

}; // namespace

#endif // LUAHOST_H
