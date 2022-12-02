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

local result = require("luasnip.extras.fmt").interpolate(
  "{a}{a}",
  { a = fake_node(1, "a") },
  { repeat_duplicates = true }
)
local str_result = ""
for _, value in pairs(result) do
  str_result = str_result .. tostring(value)
end

local ls = require("luasnip")
ls.add_snippets("all", {
  ls.s(
    "repeat",
    require("luasnip.extras.fmt").fmt([[
        {} repeat {}
        ]],
      { ls.i(1), require("luasnip.extras").rep(1) },
      { repeat_duplicates = true }
    )
  )
})
