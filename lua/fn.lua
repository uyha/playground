#!/usr/bin/env luajit

local fn = function(...)
	print(...)
end

fn({
	a = 1,
	["a"] = 1,
})
fn("asdasdsa")
