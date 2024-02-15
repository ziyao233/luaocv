/*
 *	luaocv
 *	/src/objdetect.hpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#ifndef __OBJDETECT_HPP_INC__
#define __OBJDETECT_HPP_INC__

#include<lua.hpp>

int locv_objdetect_face_detector_yn_new(lua_State *l);
int locv_objdetect_qrcode_encoder_new(lua_State *l);

void locv_objdetect_init(lua_State *l);

#endif	// __OBJDETECT_HPP_INC__
