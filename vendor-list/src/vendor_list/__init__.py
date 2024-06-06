from typing import Optional
from bs4 import BeautifulSoup


def is_supplier_type(value: str) -> bool:
    return value.startswith("⬇⬇⬇")


with open("vendor-list-from-asana.txt") as f:
    soup = BeautifulSoup(f.read(), "lxml")


suppliers: dict[str, list[str]] = dict()
current_supplier_type: Optional[str] = None

for tag in soup.select("input"):
    if "value" not in tag.attrs:
        continue

    value = tag["value"]
    assert isinstance(value, str)

    if is_supplier_type(value):
        current_supplier_type = value.strip(" ⬇").replace(" ", "-").lower()
        suppliers[current_supplier_type] = []
    elif current_supplier_type is not None:
        suppliers[current_supplier_type].append(value)

for supplier_type, sups in suppliers.items():
    with open(f"{supplier_type}.txt", "w") as f:
        for sup in sups:
            f.write(f"{sup}\n")
