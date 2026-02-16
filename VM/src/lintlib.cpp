#include <math.h>

#include "lualib.h"

#include "lvm.h"

static int i64_create(lua_State* L)
{
    luaL_checkany(L, 1);

    if (lua_type(L, 1) == LUA_TNUMBER)
    {
        double n = lua_tonumber(L, 1);
        if (floor(n) != n || n > INT64_MAX || n < INT64_MIN)
            luaL_error(L, "value cannot be precisely represented as an integer");

        lua_pushint64(L, (int64_t)n);
    }
    else if (lua_type(L, 1) == LUA_TUINT64)
    {
        uint64_t u = lua_touint64(L, 1);
        if (u > INT64_MAX)
            luaL_error(L, "value is out-of-range for a signed integer");

        lua_pushint64(L, (int64_t)u);
    }
    else
        luaL_argerror(L, 1, "expected number or uint64");

    return 1;
}

static int u64_create(lua_State* L)
{
    luaL_checkany(L, 1);

    if (lua_type(L, 1) == LUA_TNUMBER)
    {
        double n = lua_tonumber(L, 1);
        if (floor(n) != n || n > UINT64_MAX || n < 0)
            luaL_error(L, "value cannot be precisely represented as an integer");

        lua_pushuint64(L, (uint64_t)n);
    }
    else if (lua_type(L, 1) == LUA_TINT64)
    {
        int64_t i = lua_toint64(L, 1);
        if (i < 0)
            luaL_error(L, "value is negative");

        lua_pushuint64(L, (uint64_t)i);
    }
    else
        luaL_argerror(L, 1, "expected number or uint64");

    return 1;
}

static const luaL_Reg i64lib[] = {
    {"create", i64_create},
    {NULL, NULL},
};

static const luaL_Reg u64lib[] = {
    {"create", u64_create},
    {NULL, NULL},
};

int luaopen_int64(lua_State* L)
{
    luaL_register(L, LUA_I64LIBNAME, i64lib);
    return 1;
}

int luaopen_uint64(lua_State* L)
{
    luaL_register(L, LUA_U64LIBNAME, u64lib);
    return 1;
}
