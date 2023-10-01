local callback = FnMap.new()

local function create()
	local var = 0
	---@param demo Demo
	local result = function(demo)
		var = var + 1
		print(demo.a, var)
	end

	return result
end

callback.print = create()
return callback
