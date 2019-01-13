#include "LuaHost.h"

#include <memory>

namespace lib
{
    static constexpr float FLOAT_EPSILON = 1e-5f;

    struct Vec
    {
        float   x,y;

        Vec()                       : x(0), y(0) {}
        Vec(float x_, float y_)     : x(x_), y(y_) {}
        Vec(const Vec& o)           : x(o.x), y(o.y) {}

        bool operator == (const Vec& o) const {
            const float dx = x - o.x, dy = y - o.y;
            return std::abs(dx) < FLOAT_EPSILON && std::abs(dy) < FLOAT_EPSILON;
        }

        std::tuple<float,float> get() const { return std::make_tuple(x,y); }

        void set(float x_, float y_) { x = x_, y = y_; }

        Vec operator + (const Vec& o) const { return Vec(x + o.x, y + o.y); }
        const Vec& operator += (const Vec& o) { x += o.x, y += o.y; return *this; }

        float length() const        { return std::sqrt(x*x + y*y); }

        float dot(const Vec &o) const {
            return x*o.x + y*o.y;
        }

        static Vec up() { return Vec(0, 1.f); }     // static function

        Vec& ref() { return *this; }                // return ref
    };
};

//PONDER_TYPE(test::LuaTestClass)
PONDER_TYPE(lib::Vec)

void declare()
    {
        using namespace ponder;

        ponder::Class::declare<lib::Vec>()
            .constructor()
            .constructor<float, float>()
//            .constructor<const Vec&>()
            .property("x", &lib::Vec::x)
            .property("y", &lib::Vec::y)
            .function("get", &lib::Vec::get, policy::ReturnMultiple()) // tuple
            .function("set", &lib::Vec::set)
            .function("add", &lib::Vec::operator+=)
            .function("add2", &lib::Vec::operator+) //.tag("+")
            .function("length", &lib::Vec::length)
            .function("dot", &lib::Vec::dot)

            .function("up", &lib::Vec::up)   // static

            .function("funcRef", &lib::Vec::ref, policy::ReturnInternalRef())  // ref function
            .property("propRef", &lib::Vec::ref)     // ref property
            ;
    }


namespace APP_NAMESPACE {

LuaHost::LuaHost()
{
    // using namespace ponder;

    state = nullptr;

    // lib::declare();

    /*
    ponder::Class::declare<test::LuaTestClass>()
        .function("printDebug", &test::LuaTestClass::printDebug)
        ;
*/
}

LuaHost::~LuaHost()
{
    if (state != nullptr)
        free(state);
}

int LuaHost::myLuaFunction(lua_State* L)
{
	return 0;
}

int LuaHost::myLuaFunctionCallback(lua_State* L)
{
    lua_getupvalue(L, lua_upvalueindex(1), 1); //pushes the light userdata
    LuaHost* obj = static_cast<LuaHost*>(lua_touserdata(L, -1)); //gets the value of the user data
    lua_pop(L, 1); //pop userdata
    return obj->myLuaFunction(L); //call actual function
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
