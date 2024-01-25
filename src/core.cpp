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

int
locv_core_type_name_to_id(lua_State *l, int idx)
{
	const char *names[] = {
		"8uc1", "8uc3", "8uc4", "64fc1", "64fc3", "64fc4",
		NULL
	};
	int types[] = {
		CV_8UC1, CV_8UC3, CV_8UC4, CV_64FC1, CV_64FC3, CV_64FC4,
	};
	int id = luaL_checkoption(l, idx, NULL, names);
	return types[id];
}

void
locv_core_type_id_to_name(lua_State *l, int id)
{
	int ids[] = {
		CV_8UC3, CV_8UC4, CV_8UC1, CV_64FC4, CV_64FC3, CV_64FC1,
	};
	const char *names[] = {
		"8uc3", "8uc4", "8uc1", "64fc4", "64fc3", "64fc1",
	};

	for (int i = 0; i < sizeof(ids) / sizeof(int); i++) {
		if (id == ids[i]) {
			lua_pushstring(l, names[i]);
			return;
		}
	}
	locv_helper_panic("unsupported format");
}

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

static int
locv_core_mat_clone(lua_State *l)
{
	cv::Mat *mat = (cv::Mat *)locv_core_mat_in_native(l, 1);
	cv::Mat *newMat = new cv::Mat;
	mat->copyTo(*newMat);
	locv_core_mat_in_lua(l, newMat);
	return 1;
}

static void
locv_core_mat_generic_set(cv::Mat *mat, const cv::Point &p,
			  const cv::Scalar &s)
{
	int ch = mat->channels();
	const double *v = s.val;
	switch (mat->depth()) {
	case CV_8U:
		switch (ch) {
		case 1:
			mat->at<uchar>(p) = v[0];
			return;
		case 3:
			mat->at<cv::Vec3b>(p) = cv::Vec3b(v[0], v[1], v[2]);
			return;
		case 4:
			mat->at<cv::Vec4b>(p) = cv::Vec4b(v[0], v[1],
							  v[2], v[3]);
			return;
		default:
			goto error;
		}
	case CV_64F:
		switch (ch) {
		case 3:
			mat->at<cv::Vec3d>(p) = cv::Vec3d(v);
			return;
		case 4:
			mat->at<cv::Vec4d>(p) = s;
			return;
		default:
			goto error;
		}
	}
error:
	locv_helper_panic("unsupported format");
}

static int
locv_core_mat_set(lua_State *l)
{
	cv::Mat *mat = locv_core_mat_in_native(l, 1);

	void *p;
	if (luaL_testudata(l, 2, "locv.Point")) {
		cv::Point p = locv_core_point_to_native(l, 2);
		cv::Scalar s = locv_core_scalar_to_native(l, 3);
		locv_core_mat_generic_set(mat, p, s);
	} else if (luaL_testudata(l, 2, "locv.Rect")) {
		cv::Rect r = locv_core_rect_to_native(l, 2);
		cv::Scalar s = locv_core_scalar_to_native(l, 3);
		mat->operator () (r) = s;
	} else {
		luaL_typeerror(l, 2, "locv.Point or locv.Rect");
	}

	lua_settop(l, 1);
	return 1;
}

static cv::Scalar
locv_core_mat_generic_get(cv::Mat *mat, cv::Point &p)
{
	int ch = mat->channels();

	switch (mat->depth()) {
	case CV_8U:
		switch (ch) {
		case 1:
			return cv::Scalar(mat->at<uchar>(p));
		case 3:
			return cv::Scalar(mat->at<cv::Vec3b>(p));
		case 4:
			return cv::Scalar(mat->at<cv::Vec4b>(p));
		default:
			goto error;
		}
	case CV_64F:
		switch (ch) {
		case 1:
			return cv::Scalar(mat->at<double>(p));
		case 3:
			return cv::Scalar(mat->at<cv::Vec3d>(p));
		case 4:
			return cv::Scalar(mat->at<cv::Vec4d>(p));
		default:
			goto error;
		}
	}
error:
	locv_helper_panic("unsupported format");
	return cv::Scalar();
}

static int
locv_core_mat_get(lua_State *l)
{
	cv::Mat *mat = locv_core_mat_in_native(l, 1);

	void *p;
	if (luaL_testudata(l, 2, "locv.Point")) {
		cv::Point p = locv_core_point_to_native(l, 2);
		cv::Scalar s = locv_core_mat_generic_get(mat, p);
		locv_core_scalar_to_lua(l, s);
	} else if (luaL_testudata(l, 2, "locv.Rect")) {
		cv::Rect r = locv_core_rect_to_native(l, 2);
		cv::Mat *part = new cv::Mat(*mat, r);
		locv_core_mat_in_lua(l, part);
	} else {
		luaL_typeerror(l, 2, "locv.Point or locv.Rect");
	}
	return 1;
}

static int
locv_core_mat_size(lua_State *l)
{
	cv::Mat *mat = locv_core_mat_in_native(l, 1);
	locv_core_size_to_lua(l, cv::Size(mat->cols, mat->rows));
	return 1;
}

static int
locv_core_mat_format(lua_State *l)
{
	cv::Mat *mat = locv_core_mat_in_native(l, 1);
	int dep = mat->depth();
	lua_pushinteger(l, mat->channels());
	lua_pushinteger(l, dep == CV_8U ? 8 : 64);
	locv_core_type_id_to_name(l, mat->type());
	return 3;
}

int
locv_core_mat_new(lua_State *l)
{
	int top = lua_gettop(l);
	cv::Mat *mat;
	if (top) {
		int width	= luaL_checkinteger(l, 1);
		int height	= luaL_checkinteger(l, 2);
		int type 	= locv_core_type_name_to_id(l, 3);
		cv::Scalar s;
		if (top == 4)
			s = locv_core_scalar_to_native(l, 4);
		mat = new cv::Mat(width, height, type, s);
	} else {
		mat = new cv::Mat;
	}

	locv_core_mat_in_lua(l, mat);

	return 1;
}

static luaL_Reg locvCoreMatMethods[] = {
	{ "clone", locv_core_mat_clone },
	{ "set", locv_core_mat_set },
	{ "get", locv_core_mat_get },
	{ "size", locv_core_mat_size },
	{ "format", locv_core_mat_format },
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
locv_core_scalar_to_lua(lua_State *l, const cv::Scalar &scalar)
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
	for (; i < lua_gettop(l) - 1 && i < 4; i++)
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

/*		locv.Point		*/

cv::Point
locv_core_point_to_native(lua_State *l, int idx)
{
	int *p = (int *)luaL_checkudata(l, idx, "locv.Point");
	return cv::Point(p[0], p[1]);
}

void
locv_core_point_to_lua(lua_State *l, const cv::Point &point)
{
	int *p = (int *)lua_newuserdatauv(l, sizeof(int) * 2, 0);
	p[0] = point.x;
	p[1] = point.y;
	luaL_setmetatable(l, "locv.Point");
	return;
}

static int
locv_core_point_unpack(lua_State *l)
{
	int *p = (int *)luaL_checkudata(l, 1, "locv.Point");
	lua_pushinteger(l, p[0]);
	lua_pushinteger(l, p[1]);
	return 2;
}

int
locv_core_point_new(lua_State *l)
{
	int *p = (int *)lua_newuserdatauv(l, sizeof(int) * 2, 0);
	int i = 0;
	for (; i < lua_gettop(l) - 1 && i < 2; i++)
		p[i] = luaL_checkinteger(l, i + 1);
	for (; i < 2; i++)
		p[i] = 0;
	luaL_setmetatable(l, "locv.Point");
	return 1;
}

static const luaL_Reg locvCorePointMethods[] = {
	{ "unpack", locv_core_point_unpack },
	{ NULL, NULL },
};

static void
locv_core_point_init(lua_State *l)
{
	locv_helper_new_class(l, "locv.Point", locvCorePointMethods, NULL);
	return;
}

/*		locv.Size		*/

cv::Size
locv_core_size_to_native(lua_State *l, int idx)
{
	int *p = (int *)luaL_checkudata(l, idx, "locv.Size");
	return cv::Size(p[0], p[1]);
}

void
locv_core_size_to_lua(lua_State *l, const cv::Size &size)
{
	int *p = (int *)lua_newuserdatauv(l, sizeof(int) * 2, 0);
	p[0] = size.width;
	p[1] = size.height;
	luaL_setmetatable(l, "locv.Size");
	return;
}

static int
locv_core_size_unpack(lua_State *l)
{
	int *p = (int *)luaL_checkudata(l, 1, "locv.Size");
	lua_pushinteger(l, p[0]);
	lua_pushinteger(l, p[1]);
	return 2;
}

int
locv_core_size_new(lua_State *l)
{
	int *p = (int *)lua_newuserdatauv(l, sizeof(int) * 2, 0);
	p[0] = luaL_checkinteger(l, 1);
	p[1] = luaL_checkinteger(l, 2);
	luaL_setmetatable(l, "locv.Size");
	return 1;
}

static const luaL_Reg locvCoreSizeMethods[] = {
	{ "unpack", locv_core_size_unpack },
	{ NULL, NULL },
};

static void
locv_core_size_init(lua_State *l)
{
	locv_helper_new_class(l, "locv.Size", locvCoreSizeMethods, NULL);
	return;
}

/*		locv.Rect		*/
typedef struct {
	int x, y;
	int width, height;
} Locv_Core_Rect;

cv::Rect
locv_core_rect_to_native(lua_State *l, int idx)
{
	Locv_Core_Rect *rect = (Locv_Core_Rect *)
			luaL_checkudata(l, idx, "locv.Rect");
	return cv::Rect(cv::Point(rect->x, rect->y),
			cv::Size(rect->width, rect->height));
}

void
locv_core_rect_to_lua(lua_State *l, const cv::Rect &rect)
{
	Locv_Core_Rect *r = (Locv_Core_Rect *)
			lua_newuserdatauv(l, sizeof(Locv_Core_Rect), 0);
	r->x		= rect.x;
	r->y		= rect.y;
	r->width	= rect.width;
	r->height	= rect.height;
	luaL_setmetatable(l, "locv.Rect");
	return;
}

int
locv_core_rect_new(lua_State *l)
{
	cv::Point point	= locv_core_point_to_native(l, 1);
	cv::Size size	= locv_core_size_to_native(l, 2);

	Locv_Core_Rect *rect = (Locv_Core_Rect *)
			lua_newuserdatauv(l, sizeof(Locv_Core_Rect), 0);

	rect->x		= point.x;
	rect->y		= point.y;
	rect->width	= size.width;
	rect->height	= size.height;

	luaL_setmetatable(l, "locv.Rect");

	return 1;
}

int
locv_core_rect_top_left(lua_State *l)
{
	Locv_Core_Rect *rect = (Locv_Core_Rect *)
			luaL_checkudata(l, 1, "locv.Rect");
	locv_core_point_to_lua(l, cv::Point(rect->x, rect->y));
	return 1;
}

int
locv_core_rect_size(lua_State *l)
{
	Locv_Core_Rect *rect = (Locv_Core_Rect *)
			luaL_checkudata(l, 1, "locv.Rect");
	locv_core_size_to_lua(l, cv::Size(rect->width, rect->height));
	return 1;
}

static const luaL_Reg locvCoreRectMethods[] = {
	{ "topLeft", locv_core_rect_top_left },
	{ "size", locv_core_rect_size },
	{ NULL, NULL },
};

static void
locv_core_rect_init(lua_State *l)
{
	locv_helper_new_class(l, "locv.Rect", locvCoreRectMethods, NULL);
}

void
locv_core_init(lua_State *l)
{
	locv_core_mat_init(l);
	locv_core_scalar_init(l);
	locv_core_point_init(l);
	locv_core_size_init(l);
	locv_core_rect_init(l);
	return;
}
