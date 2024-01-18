/*
 *	luaocv
 *	/src/helper.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>

void
locv_helper_new_class(lua_State *l, const char *name, const luaL_Reg *methods,
		      lua_CFunction gc)
{
	luaL_newmetatable(l, name);

	lua_newtable(l);
	luaL_setfuncs(l, methods, 0);
	lua_setfield(l, -2, "__index");

	if (gc) {
		lua_pushcfunction(l, gc);
		lua_setfield(l, -2, "__gc");
	}

	lua_pop(l, 1);
	return;
}
