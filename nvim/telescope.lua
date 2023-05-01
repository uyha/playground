local pickers = require("telescope.pickers")
local finders = require("telescope.finders")
local conf = require("telescope.config").values
local actions = require("telescope.actions")
local action_state = require("telescope.actions.state")

local opts = {}

pickers
	.new(opts, {
		prompt_title = "Path to executable",
		finder = finders.new_oneshot_job({ "fd", "--hidden", "--no-ignore" }, {}),
		sorter = conf.generic_sorter(opts),
		attach_mappings = function(buffer_number)
			actions.select_default:replace(function()
				actions.close(buffer_number)
				vim.api.nvim_put(action_state.get_selected_entry(), "", false, true)
			end)
			return true
		end,
	})
	:find()
