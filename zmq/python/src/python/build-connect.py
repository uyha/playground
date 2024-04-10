import zmq
from msgpack import packb

with zmq.Context() as context, zmq.Socket(context, zmq.REQ) as client:
    client.connect("tcp://10.147.17.144:5555")
    client.send_multipart(
        [
            packb("/login"),
            packb(["KR1.2-2101-006E", "password"]),
        ]
    )
    print(client.recv())
