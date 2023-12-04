import enum


def soemthing():
    ...


class RequestCode(enum.Enum):
    invalid = enum.auto()
    valid = enum.auto()


print(RequestCode.invalid)


class Worker:
    def __init__(self, context) -> None:
        self.socket = Socket(context, Zmq.PUB)

    def yell(self):
        self.socket.send()
