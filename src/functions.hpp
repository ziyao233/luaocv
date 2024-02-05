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
#include"objdetect.hpp"
#include"imgproc.hpp"

luaL_Reg luaocvFunctions[] = {
	/*	Core		*/
	{ "Mat", locv_core_mat_new },
	{ "Scalar", locv_core_scalar_new },
	{ "Point", locv_core_point_new },
	{ "Size", locv_core_size_new },
	{ "Rect", locv_core_rect_new },

	{ "copyMakeBorder", locv_core_copy_make_border },
	{ "flip", locv_core_flip },

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

	/*	objdetect	*/
	{ "FaceDetectorYN", locv_objdetect_face_detector_yn_new },

	/*	imgproc		*/
	{ "line", locv_imgproc_line },
	{ "rectangle", locv_imgproc_rectangle },
	{ "getTextSize", locv_imgproc_get_text_size },
	{ "putText", locv_imgproc_put_text },

	{ NULL, NULL },
};

#endif	// __FUNCTIONS_HPP_INC__
