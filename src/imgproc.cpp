/*
 *	luaocv
 *	/src/imgproc.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>
#include<opencv2/imgproc.hpp>

#include"core.hpp"

static int
locv_imgproc_line_type_name_to_id(lua_State *l, int idx)
{
	const char *names[] = {
		"filled", "line4", "line8", "antialiased",
		NULL,
	};
	int ids[] = {
		cv::FILLED, cv::LINE_4, cv::LINE_8, cv::LINE_AA,
	};
	return ids[luaL_checkoption(l, idx, "line8", names)];
}

int
locv_imgproc_line(lua_State *l)
{
	cv::Mat *mat	= locv_core_mat_in_native(l, 1);
	cv::Point p1	= locv_core_point_to_native(l, 2);
	cv::Point p2	= locv_core_point_to_native(l, 3);
	cv::Scalar s	= locv_core_scalar_to_native(l, 4);
	int thickness	= luaL_optinteger(l, 5, 1);
	int type	= locv_imgproc_line_type_name_to_id(l, 6);
	cv::line(*mat, p1, p2, s, thickness, type);
	lua_settop(l, 1);
	return 1;
}

int
locv_imgproc_rectangle(lua_State *l)
{
	cv::Mat *mat = locv_core_mat_in_native(l, 1);
	cv::Point p1 = locv_core_point_to_native(l, 2);
	cv::Point p2 = locv_core_point_to_native(l, 3);
	cv::Scalar s = locv_core_scalar_to_native(l, 4);
	cv::rectangle(*mat, p1, p2, s);
	lua_settop(l, 1);
	return 1;
}

void
locv_imgproc_init(lua_State *l)
{
	return;
}
