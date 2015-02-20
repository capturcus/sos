#pragma once
#include "lua.hpp"
#include "QtCore\qstring.h"

//f has key and value on the stack on -2 and -1
template<typename F>
void traverseLuaTable(lua_State* L, F f){

	lua_pushnil(L);
	lua_checkstack(L, 3);

	while (lua_next(L, -2) != 0) {
		f(L);
		lua_pop(L, 1);
	}
}

template<typename F>
void traverseGlobalLuaTable(lua_State * L, const char* table, F f){
	lua_getglobal(L, table);
	traverseLuaTable(L, f);
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

void printLuaValue(lua_State* L, int i, int indent = 0);

void stackDump(lua_State *L);

QString luaValueToString(lua_State* L, int i);
