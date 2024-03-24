from datetime import datetime
import gzip

import zmq
from msgpack import Unpacker
from serde.msgpack import from_msgpack as unpack
from serde.msgpack import to_msgpack as pack
from io import BytesIO

with zmq.Context() as context, context.socket(zmq.REP) as receiver:
    receiver.bind("tcp://127.0.0.1:7474")
    while True:
        frames = receiver.recv_multipart(copy=False)
        name, data = unpack(tuple[str, bytes], frames[-1].bytes)
        print(b := gzip.decompress(data))
        un = Unpacker(BytesIO(b))
        print(list(un))
        receiver.send(
            a := pack(
                (0, datetime.fromisoformat("2020-01-01 00:00:00+00")),
                reuse_instances=True,
                datetime=True,
            )
        )
        print(a)
