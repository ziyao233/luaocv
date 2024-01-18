/*
 *	luaocv
 *	/src/imgcodecs.hpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#ifndef __IMGCODECS_HPP_INC__
#define __IMGCODECS_HPP_INC__

#include<lua.hpp>

int locv_imgcodecs_imread(lua_State *l);

void locv_imgcodecs_init(lua_State *l);

#endif	// __IMGCODECS_HPP_INC__
