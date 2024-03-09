def gen():
    yield 1
    raise Exception()
    yield 2


for i in gen():
    print(i)
