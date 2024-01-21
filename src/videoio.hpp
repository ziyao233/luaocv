/*
 *	luaocv
 *	/src/videoio.hpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#ifndef __VIDEOIO_HPP_INC__
#define __VIDEOIO_HPP_INC__

#include<lua.hpp>
#include<opencv2/videoio.hpp>

void locv_videoio_videocapture_in_lua(lua_State *l, cv::VideoCapture *cap);
cv::VideoCapture *locv_videoio_videocapture_in_native(lua_State *l, int idx);

int locv_videoio_videocapture_new(lua_State *l);

void locv_videoio_init(lua_State *l);

#endif	// __VIDEOIO_HPP_INC__
