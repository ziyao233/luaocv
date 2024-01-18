/*
 *	luaocv
 *	/src/highgui.hpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#ifndef __HIGHGUI_HPP_INC__
#define __HIGHGUI_HPP_INC__

int locv_highgui_imshow(lua_State *l);
int locv_highgui_waitkey(lua_State *l);

void locv_highgui_init(lua_State *l);

#endif	// __HIGHGUI_HPP_INC__
