from dataclasses import dataclass
import sqlite3


@dataclass
class Num:
    a: int


with sqlite3.connect(":memory:") as conn:
    conn.row_factory = lambda _, row: Num(*row)
    cursor = conn.execute("SELECT * FROM (VALUES (1), (2))")

    for num in cursor:
        print(num)
