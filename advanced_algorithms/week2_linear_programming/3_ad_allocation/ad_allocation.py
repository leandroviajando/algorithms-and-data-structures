from typing import List


def choose_pivot_column(m: int, n: int, s: int, A: List[List[float]]) -> int:  # noqa: N803
    minimum = -0.001
    enter = -1
    for j in range(m + n + s + 2):
        if A[-1][j] < minimum:
            minimum = A[-1][j]
            enter = j
    return enter


def gaussian_elimination(  # noqa: C901, CFQ002
    depart: int, enter: int, m: int, n: int, s: int, A: List[List[float]], b: List[float]  # noqa: N803
) -> None:
    pivot = A[depart][enter]

    if pivot != 1:
        for k in range(m + n + s + 2):
            A[depart][k] /= pivot

        b[depart] /= pivot

    for i in range(len(A)):
        if i != depart:
            a = A[i][enter]

            for j in range(m + n + s + 2):
                A[i][j] -= A[depart][j] * a

            b[i] -= b[depart] * a


def phase_one(m: int, n: int, s: int, A: List[List[float]], b: List[float], basis: List[int]) -> float:  # noqa: C901, N803
    enter = choose_pivot_column(m, n, s, A)

    while enter != -1:
        depart = -1
        min_ratio = float("inf")

        for i in range(n):
            if A[i][enter] > 0:
                ratio = b[i] / A[i][enter]

                if ratio < min_ratio:
                    min_ratio = ratio
                    depart = i

        basis[depart] = enter
        gaussian_elimination(depart, enter, m, n, s, A, b)
        enter = choose_pivot_column(m, n, s, A)

    return b[-1]


def transition(  # noqa: C901, CFQ002
    m: int, n: int, s: int, A: List[List[float]], basis: List[int], b: List[float], arti: List[int]  # noqa: N803
) -> None:
    enter = -1
    for i in range(n):
        if basis[i] in arti:
            for j in range(m + n):
                if A[i][j] != 0:
                    enter = j
                    basis[i] = j
                    break
            gaussian_elimination(i, enter, m, n, s, A, b)


def phase_two(m: int, n: int, s: int, A: List[List[float]], b: List[float], basis: List[int]) -> int:  # noqa: C901, N803
    ans = 0
    A.pop()
    b.pop()
    enter = choose_pivot_column(m, n, -2, A)

    while enter != -1:
        depart = -1
        min_ratio = float("inf")

        for i in range(n):
            if A[i][enter] > 0:
                ratio = b[i] / A[i][enter]
                if ratio < min_ratio:
                    min_ratio = ratio
                    depart = i

        if depart == -1:
            ans = 1
            break

        basis[depart] = enter
        gaussian_elimination(depart, enter, m, n, s, A, b)
        enter = choose_pivot_column(m, n, -2, A)

    return ans


def two_phase_simplex(  # noqa: C901, CFQ002
    m: int, n: int, s: int, A: List[List[float]], b: List[float], basis: List[int], arti_var: List[int]  # noqa: N803
) -> None:
    w = phase_one(m, n, s, A, b, basis)

    if w < -0.001:
        print("No solution")
    else:
        transition(m, n, s, A, basis, b, arti_var)
        ans = phase_two(m, n, s, A, b, basis)

        if ans == 1:
            print("Infinity")
        else:
            solution = [0.0] * (m + n)

            for i in range(n):
                solution[basis[i]] = b[i]

            print("Bounded solution")
            for k in range(m):
                print("{0:.18f}".format(solution[k]), end=" ")
            print()


if __name__ == "__main__":  # noqa: C901
    n, m = map(int, input().split())
    A = []
    for _ in range(n):
        A += [list(map(float, input().split()))]
    b = list(map(float, input().split()))
    c = list(map(float, input().split()))
    b.append(0)
    arti = [i for i in range(n + 1) if b[i] < 0]
    s = len(arti)
    basis = []
    arti_var = []
    count = 0
    for i in range(n):
        lst = [0] * (n + s + 2)
        lst[i] = 1
        if b[i] >= 0:
            A[i] += lst
            basis.append(m + i)
        else:
            b[i] = -b[i]
            tmp = [-e for e in A[i]]
            tmp += [-e for e in lst]
            tmp[n + m + count] = 1
            basis.append(n + m + count)
            arti_var.append(n + m + count)
            count += 1
            A[i] = tmp
    tmp = [-e for e in c] + [0] * (n + s + 2)
    tmp[-2] = 1
    A += [tmp]

    tmp = []
    for j in range(m + n):
        a = 0.0
        for e in arti:
            a += A[e][j]
        tmp.append(-a)
    tmp += [0] * (s + 2)
    tmp[-1] = 1
    A += [tmp]
    a = 0.0
    for e in arti:
        a += b[e]
    b.append(-a)

    two_phase_simplex(m, n, s, A, b, basis, arti_var)
