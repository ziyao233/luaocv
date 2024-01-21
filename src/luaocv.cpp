/*
 *	luaocv
 *	/src/luaocv.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>
#include"functions.hpp"
#include"core.hpp"

extern "C" int
luaopen_luaocv(lua_State *l)
{
	locv_core_init(l);
	locv_imgcodecs_init(l);
	locv_highgui_init(l);
	locv_videoio_init(l);
	luaL_newlib(l, luaocvFunctions);
	return 1;
}
