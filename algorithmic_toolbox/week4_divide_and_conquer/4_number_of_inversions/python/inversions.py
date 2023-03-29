import sys
from typing import MutableSequence


def get_number_of_inversions(a: MutableSequence[int], b: MutableSequence[int], left: int, right: int) -> int:
    number_of_inversions = 0

    if right <= left + 1:
        return number_of_inversions

    ave = (left + right) // 2
    number_of_inversions += get_number_of_inversions(a, b, left, ave)
    number_of_inversions += get_number_of_inversions(a, b, ave, right)
    number_of_inversions += merge(a, b, left, ave - 1, right - 1)

    return number_of_inversions


def merge(a: MutableSequence[int], b: MutableSequence[int], left: int, ave: int, right: int) -> int:  # noqa: C901
    i = left
    j = ave + 1
    k = left
    inv_count = 0

    while i <= ave and j <= right:
        if a[i] <= a[j]:
            b[k] = a[i]
            k += 1
            i += 1
        else:
            inv_count += ave - i + 1
            b[k] = a[j]
            k += 1
            j += 1

    while i <= ave:
        b[k] = a[i]
        k += 1
        i += 1

    while j <= right:
        b[k] = a[j]
        k += 1
        j += 1

    for i in range(left, right + 1):
        a[i] = b[i]

    return inv_count


if __name__ == "__main__":
    n, *a = list(map(int, sys.stdin.read().split()))
    b = n * [0]
    print(get_number_of_inversions(a, b, 0, len(a)))
