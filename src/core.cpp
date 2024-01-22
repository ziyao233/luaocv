/*
 *	luaocv
 *	/src/core.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<cassert>
#include<cstring>
#include<iostream>

#include<lua.hpp>
#include<opencv2/core.hpp>

#include"core.hpp"
#include"helper.hpp"

/*		locv.Mat		*/

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

/*		locv.Scalar		*/

cv::Scalar
locv_core_scalar_to_native(lua_State *l, int idx)
{
	double *p = (double *)luaL_checkudata(l, idx, "locv.Scalar");
	return cv::Scalar(p[0], p[1], p[2], p[3]);
}

void
locv_core_scalar_to_lua(lua_State *l, cv::Scalar &scalar)
{
	double *p = (double *)lua_newuserdatauv(l, sizeof(double) * 4, 0);
	luaL_setmetatable(l, "locv.Scalar");
	std::memcpy(p, scalar.val, sizeof(double) * 4);
	return;
}

static int
locv_core_scalar_unpack(lua_State *l)
{
	double *p = (double *)luaL_checkudata(l, 1, "locv.Scalar");
	for (int i = 0; i < 4; i++)
		lua_pushnumber(l, p[i]);
	return 4;
}

int
locv_core_scalar_new(lua_State *l)
{
	double *p = (double *)lua_newuserdatauv(l, sizeof(double) * 4, 0);
	int i = 0;
	for (; i < lua_gettop(l) - 1; i++)
		p[i] = luaL_checknumber(l, i + 1);
	for (; i < 4; i++)
		p[i] = 0.;

	luaL_setmetatable(l, "locv.Scalar");

	return 1;
}

static const luaL_Reg locvCoreScalarMethods[] = {
	{ "unpack", locv_core_scalar_unpack },
	{ NULL, NULL },
};

static void
locv_core_scalar_init(lua_State *l)
{
	locv_helper_new_class(l, "locv.Scalar", locvCoreScalarMethods, NULL);
	return;
}

void
locv_core_init(lua_State *l)
{
	locv_core_mat_init(l);
	locv_core_scalar_init(l);
	return;
}
