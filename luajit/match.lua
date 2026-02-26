local s = [[
if false then end
]]

print(s:match([[(if %s*false%s* then)().*(end)()]]))
