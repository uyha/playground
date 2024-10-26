import zmq


def main():
    context = zmq.Context()
    socket = context.socket(zmq.PUSH)
    socket.connect("ipc:///tmp/tententen")
    socket.send(b"asdfasdasdasdasdasdfasdf")


if __name__ == "__main__":
    main()
