/*
 *	luaocv
 *	/src/highgui.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>

#include"core.hpp"
#include"highgui.hpp"

int
locv_highgui_imshow(lua_State *l)
{
	const char *name = luaL_checkstring(l, 1);
	cv::Mat *mat = locv_core_mat_in_native(l, 2);

	cv::imshow(name, *mat);

	return 0;
}

int
locv_highgui_wait_key(lua_State *l)
{
	int delay = lua_tonumber(l, 1);
	int key = cv::waitKey(delay);
	lua_pushinteger(l, key);
	return 1;
}

int
locv_highgui_poll_key(lua_State *l)
{
	lua_pushinteger(l, cv::pollKey());
	return 1;
}

int
locv_highgui_set_window_title(lua_State *l)
{
	cv::setWindowTitle(luaL_checkstring(l, 1),
			   luaL_checkstring(l, 2));
	return 0;
}

void
locv_highgui_init(lua_State *l)
{
	return;
}
