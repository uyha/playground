#!/usr/bin/env lua

mods = { "378160973", "481765222"}

enabled_mods = {}

for k, v in pairs(mods) do
  enabled_mods["workshop-" .. v] = {enable = true}
end

for k, v in pairs(enabled_mods) do
  print(k, v)
end
