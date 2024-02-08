try:
    [a, b, *c] = [1, 2]
    print(c)
except ValueError:
    print("nope, lol")
