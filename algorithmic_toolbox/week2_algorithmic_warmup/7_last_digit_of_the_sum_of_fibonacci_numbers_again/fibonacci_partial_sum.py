import sys
from typing import Final


def fibonacci_partial_sum_naive(from_: int, to: int) -> int:
    sum_ = 0

    current = 0
    next_ = 1

    for i in range(to + 1):
        if i >= from_:
            sum_ += current

        current, next_ = next_, current + next_

    return sum_ % 10


PISANO_PERIOD: Final = 60


def fibonacci_partial_sum(from_: int, to: int) -> int:
    """The last digit of the numbers in the Fibonacci Sequence form a pattern that repeats after every 60th number.

    Source: https://www.goldennumber.net/fibonacci-60-repeating-pattern/"""

    fib_nums_0_through_60: list[int] = [0, 1]

    for i in range(2, PISANO_PERIOD):
        fib_nums_0_through_60.append(fib_nums_0_through_60[i - 1] + fib_nums_0_through_60[i - 2])

    from_ %= PISANO_PERIOD
    to %= PISANO_PERIOD

    sum_ = 0
    for j in range(from_, to + 1):
        sum_ += fib_nums_0_through_60[j % PISANO_PERIOD]
        sum_ %= 10

    return sum_


if __name__ == "__main__":
    from_, to = map(int, sys.stdin.read().split())
    print(fibonacci_partial_sum(from_, to))
    print(fibonacci_partial_sum_naive(from_, to))
