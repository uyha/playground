---@meta

---@class Demo
---@field a number
Demo = {}

---@return Demo
Demo.new = function() end

---@alias FnMap table<string, fun(Demo,...)>
FnMap = {}

---@return FnMap
FnMap.new = function() end
