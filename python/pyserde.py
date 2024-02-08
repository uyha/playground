from serde.json import from_json, to_json
from serde import serde, Strict


@serde(type_check=Strict)
class StrictString(str):
    pass


int_json = to_json(1)
string_json = to_json("1")

print(f"{int_json=} {string_json=}")
print(f"{from_json(StrictString, int_json)=} {from_json(StrictString, string_json)=}")
