import collections
import sys


def get_majority_element(a: list[int], left: int, right: int) -> int:
    if left == right:
        return -1
    if left + 1 == right:
        return a[left]

    most_common_element = collections.Counter(a).most_common(1)[0]

    return most_common_element[0] if most_common_element[1] > len(a) // 2 else -1


if __name__ == "__main__":
    n, *a = list(map(int, sys.stdin.read().split()))
    if get_majority_element(a, 0, n) != -1:
        print(1)
    else:
        print(0)
