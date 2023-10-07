#!/usr/bin/env luajit

local inspect = require("inspect")

local a = {}

table.insert(a, 3, 5)

for index, value in ipairs(a) do
	print(inspect({ index, value }))
end

table.insert(a, 1, 3)
print(#a)
table.insert(a, 2, 4)
print(#a)

for index, value in ipairs(a) do
	print(inspect({ index, value }))
end
