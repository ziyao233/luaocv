/*
 *	luaocv
 *	/src/imgproc.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>
#include<opencv2/imgproc.hpp>

#include"core.hpp"

int
locv_imgproc_line(lua_State *l)
{
	cv::Mat *mat = locv_core_mat_in_native(l, 1);
	cv::Point p1 = locv_core_point_to_native(l, 2);
	cv::Point p2 = locv_core_point_to_native(l, 3);
	cv::Scalar s = locv_core_scalar_to_native(l, 4);
	cv::line(*mat, p1, p2, s);
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
