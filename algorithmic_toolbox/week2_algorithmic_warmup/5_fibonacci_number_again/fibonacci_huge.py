import sys


def get_fibonacci_huge_naive(n: int, m: int) -> int:
    if n <= 1:
        return n

    previous = 0
    current = 1

    for _ in range(n - 1):
        previous, current = current, previous + current

    return current % m


def get_pisano_period(m: int) -> int:
    a, b = 0, 1
    c = a + b

    for i in range(m * m):
        c = (a + b) % m
        a = b
        b = c

        if a == 0 and b == 1:
            return i + 1

    raise Exception("could not find pisano period")


def get_fibonacci_huge(n: int, m: int) -> int:
    return get_fibonacci_huge_naive(n % get_pisano_period(m), m)


if __name__ == "__main__":
    n, m = map(int, sys.stdin.read().split())
    print(get_fibonacci_huge(n, m))
    print(get_fibonacci_huge_naive(n, m))
