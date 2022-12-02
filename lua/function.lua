local a = { b = 1 }

function a:a()
	print(self.b)
end

print(a.a ~= nil)
a:a()
