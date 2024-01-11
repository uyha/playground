from dataclasses import dataclass
from typing import Optional, Tuple, List


@dataclass
class Coordination:
    x: int
    y: int


def unpack() -> Optional[Tuple[List[str], int]]:
    decoded_data = Coordination(1, 2)
    decoded_credentials = ["aa", "123", "1"]

    match decoded_data, decoded_credentials:
        case Coordination(), [str(serial_number), str(token)]:
            return [serial_number, token], 1


def main():
    print(unpack())


if __name__ == "__main__":
    main()
