import functools
import sys
from typing import Collection


def compare(x: str, y: str) -> int:
    return int(y + x) - int(x + y)


def largest_number(a: Collection[str]) -> str:
    return "".join(sorted(a, key=functools.cmp_to_key(compare)))


if __name__ == "__main__":
    data = sys.stdin.read().split()
    a = data[1:]
    print(largest_number(a))
