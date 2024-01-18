/*
 *	luaocv
 *	/src/functions.hpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#ifndef __FUNCTIONS_HPP_INC__
#define __FUNCTIONS_HPP_INC__

#include<lua.hpp>

#include"core.hpp"
#include"imgcodecs.hpp"

luaL_Reg luaocvFunctions[] = {
	{ "Mat", locv_core_mat_new },
	{ "imread", locv_imgcodecs_imread },
	{ NULL, NULL },
};

#endif	// __FUNCTIONS_HPP_INC__
