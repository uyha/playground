#!/usr/bin/env luajit

local a = "a"

local b = #a > 0 and 1 or 2
print(b)
