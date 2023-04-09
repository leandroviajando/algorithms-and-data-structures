import sys
from typing import Iterator, Sequence


def greedy_optimal_sequence(n: int) -> Iterator[int]:  # noqa: C901
    sequence = []
    while n >= 1:
        sequence.append(n)
        if n % 3 == 0:
            n = n // 3
        elif n % 2 == 0:
            n = n // 2
        else:
            n = n - 1
    return reversed(sequence)


def optimal_sequence(n: int) -> Sequence[int]:
    dp: list[list[int]] = [[] for _ in range(n + 1)]

    for i in range(1, n + 1):
        dp[i] = (
            [1]
            if i == 1
            else [1, i]
            if i in (2, 3)
            else min((dp[int(j)] for j in (i / 3, i / 2, i - 1) if int(j) == j), key=len) + [i]
        )

    return dp[n]


if __name__ == "__main__":
    n = int(sys.stdin.read())
    sequence = list(optimal_sequence(n))
    print(len(sequence) - 1)
    for x in sequence:
        print(x, end=" ")
