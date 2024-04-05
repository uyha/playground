#!/usr/bin/env lua5.4

local sup = function()
	local a <const> = setmetatable({}, {
		__close = function()
			print("closing")
		end,
	})
	local _ <close> = a
	return a
end

sup()
