from typing import Sequence


def max_pairwise_product(numbers: Sequence[int]) -> int:  # noqa: C901
    n = len(numbers)

    index1 = 0
    for i in range(1, n):
        if numbers[i] > numbers[index1]:
            index1 = i

    index2 = 0 if index1 != 0 else 1
    for i in range(1, n):
        if i != index1 and numbers[i] > numbers[index2]:
            index2 = i

    return numbers[index1] * numbers[index2]


if __name__ == "__main__":
    n = int(input())
    numbers = [int(x) for x in input().split()]
    assert len(numbers) == n

    result = max_pairwise_product(numbers)

    print(result)
