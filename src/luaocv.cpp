/*
 *	luaocv
 *	/src/luaocv.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>

#include"functions.hpp"

extern "C" int
luaopen_luaocv(lua_State *l)
{
	luaL_newlib(l, luaocvFunctions);
	return 1;
}
