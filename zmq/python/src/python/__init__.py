import msgpack
import zmq

import datetime

with zmq.Context() as context, zmq.Socket(context, zmq.PUSH) as inserter, zmq.Socket(
    context, zmq.PUSH
) as deleter:
    deleter.get_monitor_socket()
    deleter.connect("ipc:///home/uy/Work/neobot/runtime/elmo-slave/delete")
    deleter.send(
        msgpack.packb(
            [
                1,
                msgpack.Timestamp.from_datetime(datetime.datetime.now(datetime.UTC)),
            ]
        )
    )

    for i in range(100):
        inserter.connect("ipc:///home/uy/Work/neobot/runtime/elmo-slave/insert")
        inserter.send(
            msgpack.packb(
                [
                    1,
                    [
                        msgpack.Timestamp.from_datetime(
                            datetime.datetime.now(datetime.UTC)
                            + datetime.timedelta(milliseconds=i)
                        ),
                        i,
                    ],
                ]
            )
        )
