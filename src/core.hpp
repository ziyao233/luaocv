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

void locv_core_mat_in_lua(lua_State *l, cv::Mat *mat);
cv::Mat *locv_core_mat_in_native(lua_State *l, int idx);

int locv_core_mat_new(lua_State *l);

void locv_core_init(lua_State *l);

#endif	// __CORE_HPP_INC__
