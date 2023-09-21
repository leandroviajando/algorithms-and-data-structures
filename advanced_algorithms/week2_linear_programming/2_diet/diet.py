import copy
import itertools
from typing import Callable, List, Optional, Set, cast

EPS = 1e-18
PRECISION = 18


class Position:
    def __init__(self, row: int, col: int) -> None:
        self.row = row
        self.col = col


def select_pivot_element(pivot: Position, a: List[List[float]], used_rows: List[bool]) -> Optional[Position]:
    while pivot.row < len(a) and (used_rows[pivot.row] or a[pivot.row][pivot.col] == 0):
        pivot.row += 1

    return None if pivot.row == len(a) else pivot


def swap_lines(a: List[List[float]], b: List[float], used_rows: List[bool], pivot: Position) -> None:
    a[pivot.col], a[pivot.row] = a[pivot.row], a[pivot.col]
    b[pivot.col], b[pivot.row] = b[pivot.row], b[pivot.col]
    used_rows[pivot.col], used_rows[pivot.row] = used_rows[pivot.row], used_rows[pivot.col]
    pivot.row = pivot.col


def process_pivot_element(  # noqa: C901
    a: List[List[float]], b: List[float], pivot: Position, used_rows: List[bool]
) -> None:
    scale = a[pivot.row][pivot.col]

    if scale != 1:
        for i in range(len(a)):
            a[pivot.row][i] /= scale

        b[pivot.row] /= scale

    for i in range(len(a)):
        if i != pivot.row:
            multiple = a[i][pivot.col]

            for j in range(len(a)):
                a[i][j] -= a[pivot.row][j] * multiple

            b[i] -= b[pivot.row] * multiple

    used_rows[pivot.row] = True


def find_subsets(n: int, m: int) -> List[Set[int]]:
    lst = list(range(n + m + 1))
    return list(
        map(
            cast(Callable[..., Set[int]], set),
            itertools.combinations(lst, m),
        )
    )


def gaussian_elimination(subset: set, A: List[List[int]], B: List[int]) -> Optional[List[float]]:  # noqa: N803
    a: List[List[float]] = [copy.deepcopy(A[i]) for i in subset]
    b: List[float] = [copy.deepcopy(B[i]) for i in subset]

    size = len(a)
    used_rows = [False] * size
    for i in range(size):
        if pivot := select_pivot_element(Position(0, i), a, used_rows):
            swap_lines(a, b, used_rows, pivot)
            process_pivot_element(a, b, pivot, used_rows)
        else:
            return None

    return b


def is_valid(solution: List[float], A: List[List[int]], B: List[int], m: int) -> bool:  # noqa: C901, N803
    for i in range(len(A)):
        _sum = 0.0

        for j in range(m):
            _sum += A[i][j] * solution[j]

        if _sum - B[i] > 0.00001:
            return False

    return True


def solve(subsets: List[set], A: List[List[int]], B: List[int], pleasure: List[int], m: int) -> None:  # noqa: C901, N803
    solutions = [
        solution
        for subset in subsets
        if (solution := gaussian_elimination(subset, A, B)) is not None and is_valid(solution, A, B, m)
    ]

    if not solutions:
        print("No solution")
        return

    best = float("-inf")
    result: Optional[List[float]] = None
    for s in solutions:
        p = 0.0
        for i in range(m):
            p += pleasure[i] * s[i]
        if p > best:
            best = p
            result = s

    tmp = 0.0
    if result:
        for e in result:
            tmp += e
    if tmp > 1000000000:
        print("Infinity")
    else:
        print("Bounded solution")
        if result:
            for e in result:
                print("{0:.18f}".format(e), end=" ")
        print()


if __name__ == "__main__":
    n_equations, n_variables = map(int, input().split())
    A = [list(map(int, input().split())) for i in range(n_equations)]
    B = list(map(int, input().split()))
    for i in range(n_variables):
        lst = [0] * n_variables
        lst[i] = -1
        A.append(lst)
        B.append(0)
    A.append([1] * n_variables)
    B.append(1000000001)
    pleasure = list(map(int, input().split()))

    sub = find_subsets(n_equations, n_variables)

    solve(sub, A, B, pleasure, n_variables)
