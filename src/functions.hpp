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
#include"highgui.hpp"

luaL_Reg luaocvFunctions[] = {
	/*	Core		*/
	{ "Mat", locv_core_mat_new },

	/*	imgcodecs	*/
	{ "imread", locv_imgcodecs_imread },
	{ "imwrite", locv_imgcodecs_imwrite },

	/*	highgui		*/
	{ "imshow", locv_highgui_imshow },
	{ "waitKey", locv_highgui_waitkey },
	{ NULL, NULL },
};

#endif	// __FUNCTIONS_HPP_INC__
