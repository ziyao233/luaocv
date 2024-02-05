/*
 *	luaocv
 *	/src/objdetect.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>
#include<opencv2/objdetect/face.hpp>

#include"core.hpp"
#include"objdetect.hpp"
#include"helper.hpp"

int
locv_objdetect_face_detector_yn_detect(lua_State *l)
{
	cv::Ptr<cv::FaceDetectorYN> *d = (cv::Ptr<cv::FaceDetectorYN> *)
				luaL_checkudata(l, 1, "locv.FaceDetectorYN");
	cv::Mat *out = locv_core_mat_in_native(l, 2);
	cv::Mat *in = locv_core_mat_in_native(l, 3);
	(*d)->detect(*in, *out);
	return 0;
}

static const luaL_Reg locvObjdetectFaceDetectorYNMethods[] = {
	{ "detect", locv_objdetect_face_detector_yn_detect },
	{ NULL, NULL },
};

int
locv_objdetect_face_detector_yn_new(lua_State *l)
{
	cv::Ptr<cv::FaceDetectorYN> *d = (cv::Ptr<cv::FaceDetectorYN> *)
			lua_newuserdatauv(l,
					  sizeof(cv::Ptr<cv::FaceDetectorYN>),
					  0);
	new(d) cv::Ptr<cv::FaceDetectorYN>;
	const char *model = luaL_checkstring(l, 1);
	cv::Size size = locv_core_size_to_native(l, 2);
	*d = cv::FaceDetectorYN::create(model, "", size);
	luaL_setmetatable(l, "locv.FaceDetectorYN");
	return 1;
}

static int
locv_objdetect_face_detector_yn_gc(lua_State *l)
{
	cv::Ptr<cv::FaceDetectorYN> *d = (cv::Ptr<cv::FaceDetectorYN> *)
			luaL_checkudata(l, 1, "locv.FaceDetectorYN");
	d->~Ptr<cv::FaceDetectorYN>();
	return 0;
}

static void
locv_objdetect_face_detector_yn_init(lua_State *l)
{
	locv_helper_new_class(l, "locv.FaceDetectorYN",
			      locvObjdetectFaceDetectorYNMethods,
			      locv_objdetect_face_detector_yn_gc);
	return;
}

void
locv_objdetect_init(lua_State *l)
{
	locv_objdetect_face_detector_yn_init(l);
	return;
}
