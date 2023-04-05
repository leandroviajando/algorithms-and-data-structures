import sys


def fibonacci_sum_naive(n: int) -> int:
    if n <= 1:
        return n

    previous, current, _sum = 0, 1, 1

    for _ in range(n - 1):
        previous, current = current, previous + current
        _sum += current

    return _sum % 10


def fibonacci_sum(n: int) -> int:
    """The last digit of the numbers in the Fibonacci Sequence form a pattern that repeats after every 60th number.

    Source: https://www.goldennumber.net/fibonacci-60-repeating-pattern/"""

    return fibonacci_sum_naive(n % 60)


if __name__ == "__main__":
    n = int(sys.stdin.read())
    print(fibonacci_sum(n))
    print(fibonacci_sum_naive(n))
