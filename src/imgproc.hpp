/*
 *	luaocv
 *	/src/imgproc.hpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#ifndef __IMGPROC_HPP_INC__
#define __IMGPROC_HPP_INC__

#include<lua.hpp>

int locv_imgproc_line(lua_State *l);
int locv_imgproc_rectangle(lua_State *l);
int locv_imgproc_get_text_size(lua_State *l);
int locv_imgproc_put_text(lua_State *l);

void locv_imgproc_init(lua_State *l);

#endif	// __IMGPROC_HPP_INC__
