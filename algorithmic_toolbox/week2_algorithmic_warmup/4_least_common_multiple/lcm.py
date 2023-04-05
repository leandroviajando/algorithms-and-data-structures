import sys


def lcm_naive(a: int, b: int) -> int:
    for lcm in range(1, a * b + 1):
        if lcm % a == lcm % b == 0:
            return lcm

    return a * b


def gcd(a: int, b: int) -> int:
    _min = min(a, b)
    _max = max(a, b)

    return _max if _min == 0 else gcd(_max % _min, _min)


def lcm(a: int, b: int) -> int:
    return a * b // gcd(a, b)


if __name__ == "__main__":
    a, b = map(int, sys.stdin.read().split())
    print(lcm(a, b))
    print(lcm_naive(a, b))
