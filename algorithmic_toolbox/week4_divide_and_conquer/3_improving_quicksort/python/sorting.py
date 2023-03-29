import random
import sys
from typing import MutableSequence


def partition3(a: MutableSequence[int], l: int, r: int) -> tuple[int, int]:  # noqa: C901
    x = a[l]
    j = l
    m = l
    n = r
    i = l + 1
    while i <= n:
        if a[i] < x:
            j += 1
            a[i], a[j] = a[j], a[i]
            m += 1
            a[j], a[m] = a[m], a[j]
            i += 1
        elif a[i] == x:
            j += 1
            a[i], a[j] = a[j], a[i]
            i += 1
        else:
            a[i], a[n] = a[n], a[i]
            n -= 1
    a[l], a[m] = a[m], a[l]
    return m, j


def partition2(a: MutableSequence[int], l: int, r: int) -> int:
    x = a[l]
    j = l
    for i in range(l + 1, r + 1):
        if a[i] <= x:
            j += 1
            a[i], a[j] = a[j], a[i]
    a[l], a[j] = a[j], a[l]
    return j


def randomized_quick_sort(a: MutableSequence[int], l: int, r: int, *, use_partition3: bool = True) -> None:
    if l >= r:
        return
    k = random.randint(l, r)  # nosec: CWE-330
    a[l], a[k] = a[k], a[l]
    if use_partition3:
        m, j = partition3(a, l, r)
        randomized_quick_sort(a, l, m - 1)
        randomized_quick_sort(a, j + 1, r)
    else:
        m = partition2(a, l, r)
        randomized_quick_sort(a, l, m - 1, use_partition3=False)
        randomized_quick_sort(a, m + 1, r, use_partition3=False)


if __name__ == "__main__":
    n, *a = list(map(int, sys.stdin.read().split()))
    randomized_quick_sort(a, 0, n - 1)
    for x in a:
        print(x, end=" ")
