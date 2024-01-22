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
#include"videoio.hpp"

luaL_Reg luaocvFunctions[] = {
	/*	Core		*/
	{ "Mat", locv_core_mat_new },
	{ "Scalar", locv_core_scalar_new },
	{ "Point", locv_core_point_new },
	{ "Size", locv_core_size_new },
	{ "Rect", locv_core_rect_new },

	/*	imgcodecs	*/
	{ "imread", locv_imgcodecs_imread },
	{ "imwrite", locv_imgcodecs_imwrite },

	/*	highgui		*/
	{ "imshow", locv_highgui_imshow },
	{ "waitKey", locv_highgui_wait_key },
	{ "pollKey", locv_highgui_poll_key },
	{ "setWindowTitle", locv_highgui_set_window_title },

	/*	videoio		*/
	{ "VideoCapture", locv_videoio_videocapture_new },

	{ NULL, NULL },
};

#endif	// __FUNCTIONS_HPP_INC__
