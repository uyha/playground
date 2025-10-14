#!/usr/bin/env luajit

local clock_tree = {
	hsi_rc = 8000000,
	hse_rc = 4000000,
	lse_osc = 32768,

	pll_src = {
		hsi_rc = 0.5,
		hse_rc = 1,
	},

	pll_mul = {
		x2 = 2,
		x3 = 3,
		x4 = 4,
		x5 = 5,
		x6 = 6,
		x7 = 7,
		x8 = 8,
		x9 = 9,
		x10 = 10,
		x11 = 11,
		x12 = 12,
		x13 = 13,
		x14 = 14,
		x15 = 15,
		x16 = 16,
	},
	pll_clk = function(self, config)
		local pll_src = config.pll_src or "hsi_rc"
		local pll_mul = config.pll_mul or "x2"

		return self[pll_src] * self.pll_src[pll_src] * self.pll_mul[pll_mul]
	end,

	--- @return string
	sysclk = function(self, config)
		local system_clock = config.sw or "hsi"

		return ({
			hsi = "hsi_rc",
			pll = "pll_clk",
		})[system_clock]
	end,
}

local tree = setmetatable({
	pll_src = "hsi_rc",
	pll_mul = "x2",
}, {
	__index = function(self, key)
		--- @alias Map function() : string
		--- @type string | Map | integer | table
		local value = clock_tree[key]

		if type(value) == "function" then
			--- @type string
			value = value(clock_tree, self)
		end

		if type(value) == "number" then
			return value
		end

		if type(value) == "string" then
			return self[value]
		end

		return nil
	end,
})

print(tree.sysclk)
