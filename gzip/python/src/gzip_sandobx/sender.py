import zmq
import gzip
from serde.msgpack import to_msgpack as pack

with zmq.Context() as context, context.socket(zmq.PUSH) as sender:
    sender.connect("ipc://receiver")
    content = gzip.compress(pack("asdf"))
    for b in content:
        print(b)
    sender.send(content)
