# pylint: disable=missing-module-docstring, missing-class-docstring,
# pylint: disable=missing-function-docstring, too-few-public-methods

from typing import TypeVar, Callable, Generic, Optional


T = TypeVar("T")


class Predicate(Generic[T]):
    def __init__(self, callback: Callable[[T], bool], pretty: Optional[str] = None):
        self.callback = callback
        self.pretty = pretty or "T -> bool"

    def __call__(self, value: T) -> bool:
        return self.callback(value)

    def __and__(self, callback: Callable[[T], bool]) -> "Predicate[T]":
        return Predicate(
            lambda x: self.callback(x) and callback(x),
            f"({self}) and (T -> bool)",
        )

    def __or__(self, callback: Callable[[T], bool]) -> "Predicate[T]":
        return Predicate(
            lambda x: self.callback(x) or callback(x),
            f"({self}) or (T -> bool)",
        )

    def __repr__(self) -> str:
        return self.pretty


class EvenPredicate(Predicate[T]):
    def __init__(self):
        super().__init__(lambda x: x % 2, "Even(T -> bool)")


def divisible_by_3(value):
    return value % 3 == 0


def divisible_by_5(value):
    return value % 5 == 0


pred = EvenPredicate() & divisible_by_3 | divisible_by_5

print(pred)
print(pred(5))
