from serde.msgpack import to_msgpack

from datetime import datetime

from msgpack import packb


time = datetime.fromisoformat("2020-01-01 00:00:00+00")
print(to_msgpack(time, datetime=True))
print(packb(time, datetime=True))
