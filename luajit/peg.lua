local lpeg = require("lpeg")

local p = lpeg.P
local t = p
local v = lpeg.V
local r = lpeg.R

local pattern = p({
	"S",
	S = t("[") * v("B") * t("]"),
	B = (t("=") * v("B") * t("=")) + (t("[") * v("C") * t("]")),
	C = (r("az", "AZ") + t("]")) ^ 0,
})

local match = pattern:match("[=[]=]")

print(match)
