import gzip

import zmq
from msgpack import Unpacker
from io import BytesIO

with zmq.Context() as context, context.socket(zmq.PULL) as receiver:
    receiver.bind("tcp://127.0.0.1:7474")
    while True:
        try:
            print(raw := receiver.recv())
            print(b := gzip.decompress(raw))
            unpacker = Unpacker(BytesIO(b))
            print(list(unpacker))
        except Exception:
            import traceback

            print(traceback.format_exc())
