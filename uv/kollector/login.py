#!/usr/bin/env -S uv run

# /// script
# dependencies = [
#   "pyserde",
#   "msgpack",
#   "pyzmq",
# ]
# ///

from serde import msgpack
from zmq import REQ, Context, Socket

from enum import IntEnum


class ErrorCode(IntEnum):
    invalid = 1
    ill_formed = 2
    internal_error = 3
    unauthorized = 4
    missing_delimiter = 5
    no_route = 6


pack = msgpack.to_msgpack
unpack = msgpack.from_msgpack
ebox_snum = "EBOX1.2s-2211-022"
password = "password"
with Context() as context, Socket(context, REQ) as client:
    client.connect("tcp://kollector.kewazo.com:5555")
    # client.connect("tcp://10.147.17.144:5555")
    # client.connect("tcp://3.77.0.42:5555")
    # client.connect("tcp://localhost:5555")

    client.send_multipart(
        [
            pack("/login"),
            pack([ebox_snum, password]),
        ]
    )
    print(unpack(ErrorCode, client.recv()))
