local add_arg = function(arg)
	print("add_arg: " .. arg)
end
local add_text = function(arg)
	print("add_text: " .. arg)
end

local fmt = "asdf{}{{"

local delimiters = {
	left = "{",
	right = "}",
	esc_left = "{",
	esc_right = "}",
}

local pattern = "[{}]"
local in_placeholder = false
local left = 0

local right = fmt:find(pattern, left + 1)
print("Line 22:" .. right)

local delim = fmt:sub(right, right)
print("Line 25: " .. delim)
local next_char = fmt:sub(right + 1, right + 1)
print("Line 27: " .. next_char)

if not in_placeholder and delim == next_char then
	print("Line 30: " .. fmt:sub(left + 1, right))
	left = right + 1
	print("Line 32: " .. left)
else
	assert(delim == (in_placeholder and delimiters.right or delimiters.left), "")
	local add = in_placeholder and add_arg or add_text
	print("Line 36: " .. left, right)
	add(fmt:sub(left + 1, right - 1))
	left = right
	print("Line 39: " .. left, right)
	in_placeholder = delim == delimiters.left
	print("Line 40: " .. (in_placeholder and "true" or "false"))
end

right = fmt:find(pattern, left + 1)
print("Line 45:" .. right)

delim = fmt:sub(right, right)
print("Line 48: " .. delim)
next_char = fmt:sub(right + 1, right + 1)
print("Line 50: " .. next_char)

if not in_placeholder and delim == next_char then
	print("Line 53: " .. fmt:sub(left + 1, right))
	left = right + 1
	print("Line 55: " .. left)
else
	assert(delim == (in_placeholder and delimiters.right or delimiters.left), "")
	local add = in_placeholder and add_arg or add_text
	print("Line 59: " .. left, right)
	add(fmt:sub(left + 1, right - 1))
	left = right
	print("Line 62: " .. left, right)
	in_placeholder = delim == delimiters.left
	print("Line 64: " .. (in_placeholder and "true" or "false"))
end
