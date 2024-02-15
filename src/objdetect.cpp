/*
 *	luaocv
 *	/src/objdetect.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>
#include<opencv2/objdetect.hpp>

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

static int
locv_objdetect_qrcode_encoder_encode(lua_State *l)
{
	cv::Ptr<cv::QRCodeEncoder> *e = (cv::Ptr<cv::QRCodeEncoder> *)
			luaL_checkudata(l, 1, "locv.QRCodeEncoder");
	cv::Mat *m = locv_core_mat_in_native(l, 2);
	size_t len = 0;
	const char *s = luaL_checklstring(l, 3, &len);
	(*e)->encode(std::string(s, len), *m);
	lua_settop(l, 2);
	return 1;
}

static int
locv_objdetect_qrcode_encoder_gc(lua_State *l)
{
	cv::Ptr<cv::QRCodeEncoder> *e = (cv::Ptr<cv::QRCodeEncoder> *)
			luaL_checkudata(l, 1, "locv.QRCodeEncoder");
	e->~Ptr<cv::QRCodeEncoder>();
	return 0;
}

static const luaL_Reg locvObjdetectQRCodeEncoderMethods[] = {
	{ "encode", locv_objdetect_qrcode_encoder_encode },
	{ "__gc", locv_objdetect_qrcode_encoder_gc },
	{ NULL, NULL },
};

static cv::QRCodeEncoder::Params
qrcode_encoder_get_param(lua_State *l, int idx)
{
	const char *names[] = {
		"auto", "numeric", "alphanumeric", "byte", "eci", "kanji",
		"__error__",
	};
	int ids[] = {
		cv::QRCodeEncoder::EncodeMode::MODE_AUTO,
		cv::QRCodeEncoder::EncodeMode::MODE_NUMERIC,
		cv::QRCodeEncoder::EncodeMode::MODE_ALPHANUMERIC,
		cv::QRCodeEncoder::EncodeMode::MODE_BYTE,
		cv::QRCodeEncoder::EncodeMode::MODE_ECI,
		cv::QRCodeEncoder::EncodeMode::MODE_KANJI,
		-2
	};

	cv::QRCodeEncoder::Params params;

	if (lua_isnil(l, idx));
		return params;

	luaL_checktype(l, idx, LUA_TTABLE);

	lua_getfield(l, idx, "correctionLevel");
	lua_getfield(l, idx, "mode");
	lua_getfield(l, idx, "version");

	if (!lua_isnil(l, -1)) {
		if (!lua_isinteger(l, -1))
			luaL_argerror(l, idx, "version should be an integer");
		params.version = lua_tointeger(l, -1);
	}
	if (!lua_isnil(l, -2)) {
		int id = ids[luaL_checkoption(l, -2, "__error", names)];
		if (id == -2)
			luaL_argerror(l, idx, "invalid mode");
		params.mode = (cv::QRCodeEncoder::EncodeMode)id;
	}
	if (!lua_isnil(l, -3)) {
		int level = lua_tointeger(l, -3);
		if (level > 4 || level < 1)
			luaL_argerror(l, idx, "invalid correctionLevel");
		params.correction_level =
			(cv::QRCodeEncoder::CorrectionLevel)(level - 1);
	}

	lua_pop(l, 4);

	return params;
}

int
locv_objdetect_qrcode_encoder_new(lua_State *l)
{
	cv::Ptr<cv::QRCodeEncoder> *e = (cv::Ptr<cv::QRCodeEncoder> *)
			lua_newuserdatauv(l,
					  sizeof(cv::Ptr<cv::QRCodeEncoder>),
					  0);
	new(e) cv::Ptr<cv::QRCodeEncoder>;
	*e = cv::QRCodeEncoder::create(qrcode_encoder_get_param(l, 1));
	luaL_setmetatable(l, "locv.QRCodeEncoder");
	return 1;
}

static void
locv_objdetect_qrcode_encoder_init(lua_State *l)
{
	locv_helper_new_class(l, "locv.QRCodeEncoder",
			      locvObjdetectQRCodeEncoderMethods);
	return;
}

void
locv_objdetect_init(lua_State *l)
{
	locv_objdetect_face_detector_yn_init(l);
	locv_objdetect_qrcode_encoder_init(l);
	return;
}
