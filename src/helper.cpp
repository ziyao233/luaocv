/*
 *	luaocv
 *	/src/helper.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<cstdio>
#include<cstdlib>

#include<lua.hpp>

void
locv_helper_new_class(lua_State *l, const char *name, const luaL_Reg *methods,
		      lua_CFunction gc = NULL)
{
	luaL_newmetatable(l, name);

	lua_pushvalue(l, -1);
	lua_setfield(l, -2, "__index");

	luaL_setfuncs(l, methods, 0);

	if (gc) {
		lua_pushcfunction(l, gc);
		lua_setfield(l, -2, "__gc");
	}

	lua_pop(l, 1);
	return;
}

void
locv_helper_do_panic(const char *file, size_t line,
		     const char *func, const char *msg)
{
	fprintf(stderr, "%s at %s %lu: %s", func, file, line, msg);
	std::abort();
	return;
}

void
locv_debug(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
	return;
}
