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
line_type_name_to_id(lua_State *l, int idx)
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
	int type	= line_type_name_to_id(l, 6);
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

static int
font_name_to_id(lua_State *l, int idx)
{
	const char *names[] = {
		"simplex", "plain", "duplex", "complex", "triplex",
		"complex-small", "script-simplex", "script-complex",
		"italic",
		NULL
	};
	int ids[] = {
		cv::FONT_HERSHEY_SIMPLEX, cv::FONT_HERSHEY_PLAIN,
		cv::FONT_HERSHEY_DUPLEX, cv::FONT_HERSHEY_COMPLEX,
		cv::FONT_HERSHEY_TRIPLEX, cv::FONT_HERSHEY_COMPLEX_SMALL,
		cv::FONT_HERSHEY_SCRIPT_SIMPLEX,
		cv::FONT_HERSHEY_SCRIPT_COMPLEX, cv::FONT_ITALIC,
	};
	return ids[luaL_checkoption(l, idx, NULL, names)];
}

int
locv_imgproc_get_text_size(lua_State *l)
{
	const char *s	= luaL_checkstring(l, 1);
	int font	= font_name_to_id(l, 2);
	double scale	= luaL_optnumber(l, 3, 1.);
	int thickness	= luaL_optinteger(l, 4, 1);

	int baseline;
	locv_core_size_to_lua(l, cv::getTextSize(s, font, scale,
						 thickness, &baseline));
	lua_pushinteger(l, baseline);

	return 2;
}

int
locv_imgproc_put_text(lua_State *l)
{
	cv::Mat *m	= locv_core_mat_in_native(l, 1);
	const char *s	= luaL_checkstring(l, 2);
	cv::Point p	= locv_core_point_to_native(l, 3);
	int font	= font_name_to_id(l, 4);
	cv::Scalar c	= locv_core_scalar_to_native(l, 5);
	double scale	= luaL_optnumber(l, 6, 1.);
	int thickness	= luaL_optinteger(l, 7, 1);
	int lineType	= line_type_name_to_id(l, 8);

	cv::putText(*m, s, p, font, scale, c, thickness, lineType);

	lua_settop(l, 1);

	return 1;
}

int
locv_imgproc_resize(lua_State *l)
{
	cv::Mat *dst	= locv_core_mat_in_native(l, 1);
	cv::Mat *src	= locv_core_mat_in_native(l, 2);
	cv::Size size	= locv_core_size_to_native(l, 3);

	cv::resize(*src, *dst, size);

	lua_settop(l, 1);
	return 1;
}

void
locv_imgproc_init(lua_State *l)
{
	return;
}
