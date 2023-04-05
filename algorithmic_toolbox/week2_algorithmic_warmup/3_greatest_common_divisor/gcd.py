import sys


def gcd_naive(a: int, b: int) -> int:  # noqa: C901
    current_gcd = 1

    for d in range(2, min(a, b) + 1):
        if a % d == b % d == 0:  # noqa: SIM102
            if d > current_gcd:
                current_gcd = d

    return current_gcd


def gcd_euclidean(a: int, b: int) -> int:
    _min = min(a, b)
    _max = max(a, b)

    return _max if _min == 0 else gcd_euclidean(_max % _min, _min)


if __name__ == "__main__":
    a, b = map(int, sys.stdin.read().split())
    print(gcd_naive(a, b))
    print(gcd_euclidean(a, b))
