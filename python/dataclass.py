#!/usr/bin/env -S uv run --script

from dataclasses import dataclass


@dataclass(frozen=True)
class A:
    a: int

    def __post_init__(self):
        self.a += 1


a = A(a=1)
