vim.notify("hello")

local query = vim.treesitter.query.parse(
	"cpp",
	[[
; query
]]
)
