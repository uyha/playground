import zmq
import gzip
from serde.msgpack import from_msgpack as unpack
from typing import Any

with zmq.Context() as context, context.socket(zmq.PULL) as receiver:
    receiver.bind("ipc://receiver")
    while True:
        print(unpack(Any, gzip.decompress(receiver.recv())))
