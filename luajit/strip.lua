local a = "asdfasdf\n"
local b, _ = a:gsub("%s*$", "")
print(b)
