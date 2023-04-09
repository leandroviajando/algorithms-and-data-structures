import itertools
import sys
from typing import List, Optional, Sequence


def partition3(a: Sequence[int]) -> int:  # noqa: C901
    for c in itertools.product(range(3), repeat=len(a)):
        sums: List[Optional[int]] = [None] * 3
        for i in range(3):
            sums[i] = sum(a[k] for k in range(len(a)) if c[k] == i)

        if sums[0] == sums[1] == sums[2]:
            return 1

    return 0


if __name__ == "__main__":
    n, *A = list(map(int, sys.stdin.read().split()))
    print(partition3(A))
