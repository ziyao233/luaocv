/*
 *	luaocv
 *	/src/imgcodecs.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>

#include"imgcodecs.hpp"
#include"core.hpp"
#include"helper.hpp"

int
locv_imgcodecs_imread(lua_State *l)
{
	const char *path = luaL_checkstring(l, 1);

	const char *const list[] = {
		"unchanged", "grayscale", "color", "anydepth", "anycolor"
	};
	enum cv::ImreadModes modes[] = {
		cv::IMREAD_UNCHANGED, cv::IMREAD_GRAYSCALE, cv::IMREAD_COLOR,
		cv::IMREAD_ANYDEPTH, cv::IMREAD_ANYCOLOR
	};
	int opt = luaL_checkoption(l, 2, "color", list);

	cv::Mat res = cv::imread(path, modes[opt]);

	if (!res.data) {
		lua_pushnil(l);
		lua_pushfstring(l, "Failed to read image %s", path);
		return 2;
	}

	cv::Mat *cpy = new cv::Mat(res);
	locv_core_mat_in_lua(l, cpy);

	return 1;
}

void
locv_imgcodecs_init(lua_State *l)
{
	return;
}
