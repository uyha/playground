local fake_metatable = {
  __tostring = function(self)
    return self.text
  end,
  get_jump_index = function(self)
    return self.pos
  end,
}
fake_metatable.__index = fake_metatable

local fake_node = function(index, text)
  return setmetatable({ pos = index, text = text }, fake_metatable)
end

local prolouge = nil or ""
print(string.format("1 %s 1", prolouge))
print(tostring(fake_node(1, "test")))
