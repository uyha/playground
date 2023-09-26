local script = {
	{
		command = 1,
		mask = {
			[0x10] = 1,
		},
		strings = {
			[0] = "10",
		},
	},
}

for k, v in pairs(script[1].strings) do
	print(k, v)
end
