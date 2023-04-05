import sys


def get_fibonacci_last_digit_naive(n: int) -> int:
    if n <= 1:
        return n

    previous = 0
    current = 1

    for _ in range(n - 1):
        previous, current = current, previous + current

    return current % 10


def get_fibonacci_last_digit_optimized(n: int) -> int:
    if n <= 1:
        return n

    previous = 0
    current = 1

    for _ in range(n - 1):
        previous, current = current, (previous + current) % 10

    return current


if __name__ == "__main__":
    n = int(sys.stdin.read())
    print(get_fibonacci_last_digit_naive(n))
    print(get_fibonacci_last_digit_optimized(n))
