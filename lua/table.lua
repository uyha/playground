local metatable = {
  __tostring = function(self)
    return tostring(self.a)
  end,
  somefn = function(self)
    return self.a
  end,
}
metatable.__index = metatable
local a = setmetatable({ a = 2 }, metatable)
print(table.concat({a}))

