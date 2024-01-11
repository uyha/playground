import msgpack
from dataclasses import dataclass
import dataclasses
from typing import Tuple
import enum


@dataclass
class MyObject:
    b: Tuple[int]
    a: int = 255


class ErrorCode(enum.IntEnum):
    success = enum.auto()


def encode(obj):
    if dataclasses.is_dataclass(obj):
        return dataclasses.astuple(obj)


packer = msgpack.Packer(default=encode)
print(a := packer.pack(MyObject((1,))))
print(MyObject(*msgpack.unpackb(a)))
