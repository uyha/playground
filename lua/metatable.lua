local Node = {}

function Node:new()
  self.__index = self
  -- return setmetatable({}, self)
  return {}
end

function Node:hi()
  print("Hello")
end

local node = Node:new()

node:hi()
