/*
 *	luaocv
 *	/src/helper.hpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#ifndef __HELPER_HPP_INC__
#define __HELPER_HPP_INC__

#include<cassert>
#include<cstdarg>

#include<lua.hpp>

#define luaf extern "C"
#define locv_helper_panic(s) \
	locv_helper_do_panic(__FILE__, __LINE__, __func__, s)

void locv_helper_new_class(lua_State *l, const char *name,
			   const luaL_Reg *methods, lua_CFunction gc = NULL);
void locv_helper_do_panic(const char *file, size_t line,
			  const char *func, const char *msg);

#ifndef LOCV_RELEASE

void locv_debug(const char *fmt, ...);
#define locv_assert assert

#else

static inline void
locv_debug(const char *fmt, ...)
{
	(void)fmt;
	return;
}

#define locv_assert

#endif

#endif	// __HELPER_HPP_INC__
