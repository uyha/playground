from zmq import Context, Socket, SocketType

with Context() as context, Socket(context, SocketType.PUSH) as socket:
    socket.connect("ipc://hello")

    while True:
        socket.send_string("asdf")
