/*
 *	luaocv
 *	/src/helper.hpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#ifndef __HELPER_HPP_INC__
#define __HELPER_HPP_INC__

#include<lua.hpp>

#define luaf extern "C"

void locv_helper_new_class(lua_State *l, const char *name,
			   const luaL_Reg *methods, lua_CFunction gc);

#endif	// __HELPER_HPP_INC__
