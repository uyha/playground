from zmq import Context, Socket, SocketType

with Context() as context, Socket(context, SocketType.PUSH) as socket:
    socket.connect("tcp://192.168.1.251:8080")

    while True:
        socket.send_string("asdf")
