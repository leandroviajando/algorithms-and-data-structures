from __future__ import annotations

import sys
from typing import Generic, List, TypeVar

T = TypeVar("T", int, float)


class StackWithMax(Generic[T]):
    def __init__(self) -> None:
        self.__stack: List[T] = []

    def push(self, a: T) -> None:
        self.__stack.append(a)

    def pop(self) -> None:
        assert len(self.__stack)

        self.__stack.pop()

    def max(self) -> T:  # noqa: A003
        assert len(self.__stack)

        return max(self.__stack)


if __name__ == "__main__":  # noqa: C901
    stack: StackWithMax[int] = StackWithMax()

    n = int(sys.stdin.readline())
    for _ in range(n):
        query = sys.stdin.readline().split()

        if query[0] == "push":
            stack.push(int(query[1]))
        elif query[0] == "pop":
            stack.pop()
        elif query[0] == "max":
            print(stack.max())
