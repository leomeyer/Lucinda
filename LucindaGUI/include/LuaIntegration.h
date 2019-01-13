#ifndef LUAINTEGRATION_H
#define LUAINTEGRATION_H

#include "GlobalDefines.h"
#include "Context.h"
#include "Logger.h"

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

#include <wx/wx.h>

namespace APP_NAMESPACE {

// interface for delegate classes that can be called from Lua scripts
class LuaFunctions {
public:
    LuaFunctions(Context* context) {
        this->context = context;
    };

    virtual void defineChannel(int channel, int test) = 0;

protected:
    Context* context;
};

// This macro must be called in the implementation file for each class that implements LuaFunctions.
// Must be called from the top namespace!
#define MAKE_LUA_AVAILABLE(T) \
    PONDER_TYPE(T) \
    \
    ponder::Class::declare<T>() \
        .function("defineChannel", &T::defineChannel) \
        ;

class LuaIntegration
{
    public:
        LuaIntegration(Context* context, LuaFunctions* functions);
        virtual ~LuaIntegration();

        // throws std::exceptions if something goes wrong
        void runFile(wxString filename);

    protected:
        Context* context;

        lua_State* state;

    private:
};

};  // namespace

#endif // LUAINTEGRATION_H
