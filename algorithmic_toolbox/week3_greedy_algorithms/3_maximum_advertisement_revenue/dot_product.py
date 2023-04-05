import sys
from typing import Sequence


def max_dot_product(a: Sequence[int], b: Sequence[int]) -> int:
    a, b = sorted(a), sorted(b)

    return sum([a[i] * b[i] for i in range(len(a))])


if __name__ == "__main__":
    data = list(map(int, sys.stdin.read().split()))
    n = data[0]
    a = data[1 : (n + 1)]
    b = data[(n + 1) :]
    print(max_dot_product(a, b))
