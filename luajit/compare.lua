#!/usr/bin/env luajit

local function a() end

local b = {}
local c = {}

print(a == a)
print(b == c)

local map = {}

map[a] = b
map[a] = c

print(map[a] == b)
print(map[a] == c)
