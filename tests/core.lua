--[[
--	luaocv
--	/tests/core.lua
--	This file is distributed under MIT License.
--	Copyright (c) 2024 Yao Zi. All rights reserved.
--]]

local string		= require "string";

local locv		= require "luaocv";
local runtests		= require "runtest";

local function
sizeConstructor()
	locv.Size(1, 2);
end

local function
sizeConstructorFewerArgFail()
	locv.Size(1);
end

local function
sizeConstructorFloatArgFail()
	locv.Size(1.2);
end

local function
sizeUnpack()
	local a, b = locv.Size(20, 10):unpack();
	assert(a == 20 and b == 10);
end

local function
sizeAdd()
	local off = locv.Size(10, 10);
	local a, b = locv.Size(1, 2):add(off):unpack();
	assert(a == 11, b == 12);
end

local function
sizeAddArgFail()
	locv.Size(1, 2):add(1, 2);
end

local function
sizeToString()
	assert(locv.Size(1, 2):tostring() == "(1, 2)");
	assert(tostring(locv.Size(1, 2)) == "(1, 2)");
end

local function
rectConstructor()
	locv.Rect(locv.Point(1, 2), locv.Size(3, 4));
end

local function
rectConstructorFail()
	locv.Rect();
end

local function
matConstructor()
	locv.Mat();
	locv.Mat(10, 10, "8uc3");
	locv.Mat(10, 10, "8uc3", locv.Scalar());

	local types = { "8uc1", "8uc3", "8uc4", "64fc1", "64fc3",
			"64fc4", "32sc1", "32fc1" };
	for _, t in ipairs(types) do
		locv.Mat(1, 1, t);
	end
end

local function
matConstructorFail1()
	locv.Mat(1);
end

local function
matConstructorFail2()
	locv.Mat(1, 2);
end

local function
matConstructorFail3()
	locv.Mat("a");
end

local function
matGet()
	local m = locv.Mat(4, 4, "8uc3");
	m:get(locv.Point(3, 3));
	m:get(locv.Rect(locv.Point(1, 1), locv.Size(2, 2)));
end

local function
matGetOutOfBoundFail1()
	locv.Mat(4, 4, "8uc3"):get(locv.Point(3, 4));
end

local function
matGetOutOfBoundFail2()
	locv.Mat(4, 4, "8uc3"):get(locv.Point(4, 3));
end

local function
matGetOutOfBoundFail3()
	locv.Mat(4, 4, "8uc3"):get(
		locv.Rect(locv.Point(2, 2), locv.Size(4, 3)));
end

local function
matSet()
	local m = locv.Mat(4, 4, "8uc3");
	m:set(locv.Point(3, 3), locv.Scalar());
	m:set(locv.Rect(locv.Point(1, 1), locv.Size(2, 2)), locv.Scalar());
end

local function
matSetOutOfBoundFail1()
	locv.Mat(4, 4, "8uc3"):set(locv.Point(3, 4), locv.Scalar());
end

local function
matSetOutOfBoundFail2()
	locv.Mat(4, 4, "8uc3"):set(locv.Point(4, 3), locv.Scalar());
end

local function
matSetOutOfBoundFail3()
	locv.Mat(4, 4, "8uc3"):set(
		locv.Rect(locv.Point(2, 2), locv.Size(4, 3)),
		locv.Scalar());
end

runtests.run(
{
	{ "Size.constructor", sizeConstructor },
	{ "Size.unpack", sizeUnpack },
	{ "Size.add", sizeAdd },
	{ "Size.toString", sizeToString },
	{ "Rect.constructor", rectConstructor },
	{ "Mat.constructor", matConstructor },
	{ "Mat.get", matGet },
	{ "Mat.set", matSet },
},
{
	{ "Size.constructorFewerArgFail", sizeConstructorFewerArgFail },
	{ "Size.constructorFloatArgFail", sizeConstructorFloatArgFail },
	{ "Size.addArgFail", sizeAddArgFail },
	{ "Rect.constructorFail", rectConstructorFail },
	{ "Mat.constructorFail1", matConstructorFail1 },
	{ "Mat.constructorFail2", matConstructorFail2 },
	{ "Mat.constructorFail3", matConstructorFail3 },
	{ "Mat.getOutOfBoundFail1", matGetOutOfBoundFail1 },
	{ "Mat.getOutOfBoundFail2", matGetOutOfBoundFail2 },
	{ "Mat.getOutOfBoundFail3", matGetOutOfBoundFail3 },
	{ "Mat.setOutOfBoundFail1", matSetOutOfBoundFail1 },
	{ "Mat.setOutOfBoundFail2", matSetOutOfBoundFail2 },
	{ "Mat.setOutOfBoundFail3", matSetOutOfBoundFail3 },
});
