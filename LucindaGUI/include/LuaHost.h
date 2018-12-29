#ifndef LUAHOST_H
#define LUAHOST_H

#include "GlobalDefines.h"

extern "C" {
#include "lua/lstate.h"
}

#include <wx/wx.h>

namespace APP_NAMESPACE {

class LuaHost
{
    public:
        LuaHost();
        virtual ~LuaHost();

        // throws std::exceptions if something goes wrong
        void runFile(wxString filename);

        int myLuaFunction(lua_State* L);

        static int myLuaFunctionCallback(lua_State* L);

    protected:
        lua_State* state;

    private:
};

}; // namespace

#endif // LUAHOST_H
