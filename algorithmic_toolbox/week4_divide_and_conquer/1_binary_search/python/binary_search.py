import sys


def binary_search(a: list[int], x: int) -> int:  # noqa: C901
    left, right = 0, len(a) - 1

    while left <= right:
        mid = (left + right) // 2

        if a[mid] == x:
            return mid

        if a[mid] < x:
            left = mid + 1
        else:
            right = mid - 1

    return -1


def linear_search(a: list[int], x: int) -> int:
    for i in range(len(a)):
        if a[i] == x:
            return i
    return -1


if __name__ == "__main__":
    data = list(map(int, sys.stdin.read().split()))
    n = data[0]
    m = data[n + 1]
    a = data[1 : n + 1]
    for x in data[n + 2 :]:
        print(binary_search(a, x), end=" ")
