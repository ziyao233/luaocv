/*
 *	luaocv
 *	/src/core.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<cassert>
#include<iostream>

#include<lua.hpp>
#include<opencv2/core.hpp>

#include"core.hpp"
#include"helper.hpp"

/*
 *	locv.Mat()
 */
void
locv_core_mat_in_lua(lua_State *l, cv::Mat *mat)
{
	cv::Mat **p = (cv::Mat **)lua_newuserdatauv(l, sizeof(cv::Mat *), 0);
	*p = mat;

	luaL_setmetatable(l, "locv.Mat");

	return;
}

cv::Mat *
locv_core_mat_in_native(lua_State *l, int idx)
{
	cv::Mat **p = (cv::Mat **)luaL_checkudata(l, idx, "locv.Mat");
	return *p;
}

static int
locv_core_mat_gc(lua_State *l)
{
	cv::Mat *mat = locv_core_mat_in_native(l, -1);
	assert(mat);
	delete mat;
	return 0;
}

int
locv_core_mat_new(lua_State *l)
{
	cv::Mat *mat = new cv::Mat;
	locv_core_mat_in_lua(l, mat);
	return 1;
}

static luaL_Reg locvCoreMatMethods[] = {
	{ NULL, NULL },
};

static void
locv_core_mat_init(lua_State *l)
{
	locv_helper_new_class(l, "locv.Mat", locvCoreMatMethods,
			      locv_core_mat_gc);
	return;
}

void
locv_core_init(lua_State *l)
{
	locv_core_mat_init(l);
	return;
}
