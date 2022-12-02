local result = require("luasnip.extras.fmt").interpolate("{a} {a}", {a = 5})

for key, value in ipairs(result) do
  print(key, value)
end
