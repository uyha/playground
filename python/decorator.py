import time

def elapsed_time(func):
    def wrapper(*arg):
        t = time.time()
        res = func(*arg)
        print(time.time() - t)
        return res
    return wrapper

@elapsed_time
def test():
    ...

test()

