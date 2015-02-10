#include "lua-utils.h"

#pragma comment(lib, "lua.lib");

void printLuaValue(lua_State* L, int i){
	int t = lua_type(L, i);
	switch (t) {

	case LUA_TSTRING:  /* strings */
		printf("`%s'", lua_tostring(L, i));
		break;

	case LUA_TBOOLEAN:  /* booleans */
		printf(lua_toboolean(L, i) ? "true" : "false");
		break;

	case LUA_TNUMBER:  /* numbers */
		printf("%g", lua_tonumber(L, i));
		break;

	default:  /* other values */
		printf("%s", lua_typename(L, t));
		break;
	}
}

static void stackDump(lua_State *L) {
	int i;
	int top = lua_gettop(L);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		printLuaValue(L, i);
		printf("\n");  /* put a separator */
	}
	printf("\n");  /* end the listing */
}

void callLua_(lua_State* L, int argnum, const char* str)
{
	lua_getglobal(L, str);
	lua_call(L, argnum, LUA_MULTRET);
}