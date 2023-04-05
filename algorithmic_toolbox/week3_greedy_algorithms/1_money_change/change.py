import sys


def get_change(m: int) -> int:
    n = m % 10
    o = n % 5

    return m // 10 + n // 5 + o // 1


if __name__ == "__main__":
    m = int(sys.stdin.read())
    print(get_change(m))
