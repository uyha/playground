def fun1():
    ...


def fun2():
    ...


def fun3():
    ...


cache = dict()

cache[fun1] = 1
cache[fun2] = 2
cache[fun3] = 3

print(cache[fun1])
