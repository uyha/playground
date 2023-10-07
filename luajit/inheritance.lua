#!/usr/bin/env luajit

local Base = {}

function Base:new(name)
	return setmetatable({ name = name or "Annonymous" }, { __index = self })
end

function Base:hello()
	print(self.name)
end

local Derive = setmetatable({}, { __index = Base })
function Derive:new(name)
	local result = Base:new(name)
	setmetatable(result, { __index = Derive })
	return result
end
-- function Derive:hello()
-- 	print("Derive " .. self.name)
-- end

local base = Base:new()
base:hello()

local derive = Derive:new()
derive:hello()
