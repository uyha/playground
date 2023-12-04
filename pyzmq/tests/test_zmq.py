import zmq
import logging

logger = logging.getLogger(__name__)


def test_se():
    with zmq.Context() as context:
        sender = context.socket(zmq.DEALER)
        receiver = context.socket(zmq.REP)

        sender.bind("inproc://sup")
        receiver.connect("inproc://sup")

        sender.send(b"asdf", zmq.SNDMORE)
        sender.send(b"asdf", zmq.SNDMORE)
        sender.send(b"asdf", zmq.SNDMORE)
        sender.send(b"asdf", zmq.SNDMORE)
        sender.send(b"asdf", zmq.SNDMORE)
        sender.send(b"", zmq.SNDMORE)
        sender.send_pyobj([i for i in range(10)])

        assert receiver.recv_pyobj() == [i for i in range(10)]

        receiver.send_pyobj([i for i in range(5)])

        assert sender.recv() == b"asdf"
        assert sender.recv() == b"asdf"
        assert sender.recv() == b"asdf"
        assert sender.recv() == b"asdf"
        assert sender.recv() == b"asdf"
        assert sender.recv() == b""
        assert sender.recv_pyobj() == [i for i in range(5)]
