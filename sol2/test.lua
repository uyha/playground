function fn()
	for i = 1, 10, 1 do
		local lifetime <close> = Lifetime.new()
	end
end

local lifetime = Lifetime.new()
fn()
