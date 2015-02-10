#pragma once
#include "lua.hpp"

//f has key and value on the stack on -2 and -1
template<typename F>
void traverseLuaTable(lua_State* L, const char* table, F f){

	lua_getglobal(L, table);
	lua_pushnil(L);

	while (lua_next(L, -2) != 0) {
		f(L);
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
}


void callLua_(lua_State* L, int argnum, const char* str);

template<typename... Args>
void callLua_(lua_State* L, int argnum, const char* str, Args... args) // recursive variadic function
{
	lua_getglobal(L, str);

	callLua_(L, argnum + 1, args...);
}

template<typename... Args>
void callLua(lua_State* L, Args... args)
{
	callLua_(lua_State* L, 0, args...);
}

void printLuaValue(lua_State* L, int i);

static void stackDump(lua_State *L);