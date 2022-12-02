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
  return setmetatable({ pos = pos, text = text }, fake_metatable)
end
local result_table = require("luasnip.extras.fmt").interpolate(
  "{a}{a}",
  { a = fake_node(1, "a") },
  { repeat_duplicates = true }
)
local result_string = ""
for _, value in pairs(result_table) do
  result_string = result_string .. tostring(value)
end
return result_string
