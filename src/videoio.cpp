/*
 *	luaocv
 *	/src/videoio.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<cassert>

#include<lua.hpp>
#include<opencv2/videoio.hpp>

#include"core.hpp"
#include"videoio.hpp"
#include"helper.hpp"

void
locv_videoio_videocapture_in_lua(lua_State *l, cv::VideoCapture *cap)
{
	cv::VideoCapture **p = (cv::VideoCapture **)
				lua_newuserdatauv(l,
						  sizeof(cv::VideoCapture **),
						  0);
	*p = cap;

	luaL_setmetatable(l, "locv.VideoCapture");

	return;
}

cv::VideoCapture *
locv_videoio_videocapture_in_native(lua_State *l, int idx)
{
	cv::VideoCapture **p = (cv::VideoCapture **)
					luaL_checkudata(l, idx,
							"locv.VideoCapture");
	return *p;
}

static int
locv_videoio_videocapture_gc(lua_State *l)
{
	cv::VideoCapture *cap = locv_videoio_videocapture_in_native(l, 1);
	assert(cap);
	free(cap);
	return 0;
}

int
locv_videoio_videocapture_new(lua_State *l)
{
	cv::VideoCapture *cap = new cv::VideoCapture;
	if (lua_gettop(l) == 1) {
		int index = luaL_checkinteger(l, 1);
		if (!cap->open(index)) {
			delete cap;
			lua_pushboolean(l, false);
			return 1;
		}
	}

	locv_videoio_videocapture_in_lua(l, cap);

	return 1;
}

static int
locv_videoio_videocapture_read(lua_State *l)
{
	cv::VideoCapture *cap = locv_videoio_videocapture_in_native(l, 1);

	cv::Mat *mat = locv_core_mat_in_native(l, 2);

	lua_pushboolean(l, cap->read(*mat));
	return 1;
}

static const luaL_Reg locvVideoioVideoCaptureMethods[] = {
	{ "read", locv_videoio_videocapture_read },
	{ NULL, NULL },
};

static
void locv_videoio_videocapture_init(lua_State *l)
{
	locv_helper_new_class(l, "locv.VideoCapture",
			      locvVideoioVideoCaptureMethods,
			      locv_videoio_videocapture_gc);
	return;
}

void
locv_videoio_init(lua_State *l)
{
	locv_videoio_videocapture_init(l);
	return;
}
