local snake_case = function(str)
	str = str:gsub("::", "/")
	str = str:gsub("(%u+)(%u%l)", "%1_%2")
	str = str:gsub("(%u+)(%u%l)", "%1_%2")
	str = str:gsub("(%l)(%u)", "%1_%2")
	str = str:gsub("(%d)(%u)", "%1_%2")
	str = str:gsub("[.-]", "_")
	return str:lower()
end

local camel_case = function(str)
	str = str:gsub("-", "_")

	local _start, _end = str:find("^_+")
	_start = _start or 0
	_end = _end or 0

	str = str:sub(_start, _end) .. str:sub(_end + 1):gsub("_(%l)", string.upper)
	return str
end

local mixed_case = function(str)
	str = camel_case(str):gsub("^(_*%l)", string.upper)
	return str
end
