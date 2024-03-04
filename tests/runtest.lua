--[[
--	runtest.lua
--	This file is distributed under MIT License.
--	Copyright (c) 2024 Yao Zi. All rights reserved.
--]]


local io	= require "io";
local string	= require "string";
local os	= require "os";

local function
runCase(case, expect)
	local ret, msg = pcall(case);
	return ret == expect, msg;
end

local function
fmt(msg)
	return msg .. ((" "):rep(40 - #msg));
end

local function
log(msg)
	if msg then
		print(("-"):rep(80));
		print(msg);
		print(("-"):rep(80));
	end
	return;
end

local function
validate(name, code)
	local nameOk, codeOk = type(name) == "string", type(code) == "function";
	if not nameOk or not codeOk then
		log(("Invalid test case: invalid %s"):
		    format(not nameOk and "name" or ("code(%s)"):format(name)));
		os.exit(1);
	end
	return;
end

local function
runAllCases(succeed, fail)
	local unexpected = 0;
	for _, case in ipairs(succeed) do
		local name, code = case[1], case[2];
		validate(name, code);

		io.write(fmt(name));

		local ret, msg = runCase(code, true);
		if ret then
			io.write("[OK], expected\n");
		else
			io.write("[FAIL], unexpected\n");
			log(msg);
			unexpected = unexpected + 1;
		end
	end

	for _, case in ipairs(fail) do
		local name, code = case[1], case[2];
		validate(name, code);

		io.write(fmt(name));

		local ret, msg = runCase(code, false);
		if ret then
			io.write("[FAIL], expected\n");
		else
			io.write("[OK], unexpected\n");
			log(msg);
			unexpected = unexpected + 1;
		end
	end

	local total = #succeed + #fail;
	local expected = total - unexpected;
	print("total: \t\t" .. tostring(total));
	print("expected: \t" .. tostring(expected));
	print("unexpected: \t" .. tostring(unexpected));
	print(("expected/total: %.1f%%"):format(expected / total * 100));
end

return {
	run	= runAllCases,
       };
