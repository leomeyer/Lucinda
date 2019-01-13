#ifndef LUAHOST_H
#define LUAHOST_H

#include "GlobalDefines.h"
#include "Context.h"
#include "Logger.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
}

#define PONDER_USES_LUA_IMPL
#define PONDER_USES_RUNTIME_IMPL
#include <ponder/class.hpp>
#include <ponder/classbuilder.hpp>
#include <ponder/uses/lua.hpp>

// required for Ponder
static_assert(LUA_VERSION_NUM==503, "Expecting Lua 5.3");

#include <wx/wx.h>

namespace test {

class LuaTestClass {
public:
    APP_NAMESPACE::Context* context;

    LuaTestClass(APP_NAMESPACE::Context* context) {
        this->context = context;
    }

    void printDebug(const char* str) {
        context->logger->logDebug(wxString(str));
    }
};

};


namespace APP_NAMESPACE {


class LuaHost
{
    public:
        LuaHost();
        virtual ~LuaHost();
/*
        template <class T>
        void exposeObject(const char* name) {
            ponder::lua::expose<T>(state, name);
        }
*/
        // throws std::exceptions if something goes wrong
        void runFile(wxString filename);

        int myLuaFunction(lua_State* L);

        static int myLuaFunctionCallback(lua_State* L);

    protected:
        lua_State* state;
 //       test::LuaTestClass* testClass;

    private:
};

}; // namespace

#endif // LUAHOST_H
