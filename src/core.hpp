/*
 *	luaocv
 *	/src/core.hpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#ifndef __CORE_HPP_INC__
#define __CORE_HPP_INC__

#include<lua.hpp>
#include<opencv2/core.hpp>

int locv_core_type_name_to_id(lua_State *l, int idx);
void locv_core_type_id_to_name(lua_State *l, int idx);

void locv_core_mat_in_lua(lua_State *l, cv::Mat *mat);
cv::Mat *locv_core_mat_in_native(lua_State *l, int idx);

void locv_core_scalar_to_lua(lua_State *l, const cv::Scalar &scalar);
cv::Scalar locv_core_scalar_to_native(lua_State *l, int idx);

void locv_core_point_to_lua(lua_State *l, const cv::Point &point);
cv::Point locv_core_point_to_native(lua_State *l, int idx);

void locv_core_size_to_lua(lua_State *l, const cv::Size &size);
cv::Size locv_core_size_to_native(lua_State *l, int idx);

void locv_core_rect_to_lua(lua_State *l, const cv::Rect &rect);
cv::Rect locv_core_rect_to_native(lua_State *l, int idx);

int locv_core_mat_new(lua_State *l);
int locv_core_scalar_new(lua_State *l);
int locv_core_point_new(lua_State *l);
int locv_core_size_new(lua_State *l);
int locv_core_rect_new(lua_State *l);

void locv_core_init(lua_State *l);

#endif	// __CORE_HPP_INC__
