from dataclasses import dataclass


import serde

from serde import msgpack
from serde import toml


@serde.serde(type_check=serde.Strict)
@dataclass
class Sub:
    sub: str


@serde.serde(type_check=serde.Strict)
@dataclass
class Config:
    name: str
    sub: Sub
    other: float | int = 1.0


a = {
    "name": "",
    "sub": {"sub": ""},
    "other": 1,
}
config = serde.from_dict(Config, a)
print(raw_bytes := msgpack.to_msgpack(config, named=False))
print(msgpack.from_msgpack(Config, raw_bytes, named=False))
print(toml.to_toml(config))
