from contextlib import contextmanager


@contextmanager
def sup():
    print("woa")
    try:
        yield
    finally:
        print("aow")


with sup():
    raise Exception()
