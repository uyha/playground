#!/usr/bin/env luajit

local content = [[
if (false) {

}
]]
local _, _, open, close = content:find("(if%s*%(false%)%s*{).*(})")
print(open, close)
