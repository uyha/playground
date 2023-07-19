#!/usr/bin/env luajit
local Node = {}

function Node:new()
	local vars = {}

	return setmetatable({}, {
		__index = function(_, key)
			print(key)
			return self[key]
		end,
		__newindex = function(_, key, value)
			vars[key] = value
			print(vars[key])
		end,
	})
end

function Node:hi()
	print("Hello")
end

local node = Node:new()

node:hi()
node.a = 1
node.a = node.a + 1
