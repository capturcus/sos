#include "lua-utils.h"

#pragma comment(lib, "lua.lib")

static inline void printPadding(int pad){
	while (pad--)
		putchar(' ');
}

void printLuaValue(lua_State* L, int i, int indent){
	int t = lua_type(L, i);

	printPadding(indent);
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

	case LUA_TTABLE:
		printf("[TABLE START]\n");
		traverseLuaTable(L, [=](lua_State * L){
			printLuaValue(L, -2, indent + 2);
			printf(" => ");
			printLuaValue(L, -1, indent + 2);
			putchar('\n');
		});
		printPadding(indent);
		printf("[TABLE END]");
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