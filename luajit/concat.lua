#!/usr/bin/env luajit

local s1 = string.char(unpack({ 0x30, 0x31, 0x00, 0x00, 0x30 }))
local s2 = "01" .. "1"

local map = { 1, 2, 3 }
local a, b, c = unpack(map)

print(a, b, c)
