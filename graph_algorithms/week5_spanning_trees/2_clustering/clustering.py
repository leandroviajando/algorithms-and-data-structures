import math
from typing import List, Optional, Tuple


def find(parent: List[int], i: int) -> int:
    if i != parent[i]:
        parent[i] = find(parent, parent[i])
    return parent[i]


def union(parent: List[int], rank: List[int], i: int, j: int) -> None:  # noqa: C901
    i_parent = find(parent, i)
    j_parent = find(parent, j)
    if i_parent == j_parent:
        return

    if rank[i_parent] > rank[j_parent]:
        parent[j_parent] = i_parent
    else:
        parent[i_parent] = j_parent
        if rank[i_parent] == rank[j_parent]:
            rank[j_parent] += 1


def min_distance_clustering(edges: List[Tuple[int, int, float]], n: int, k: int) -> float:  # noqa: C901
    parent = list(range(n))
    rank = [0] * n
    n_edge = 0
    edges.sort(key=lambda i: i[2])
    for u, v, w in edges:
        if find(parent, u) != find(parent, v):
            if n_edge == n - k:
                return w

            n_edge += 1
            union(parent, rank, u, v)
    return 0


if __name__ == "__main__":  # noqa: C901
    n_vertices = int(input())
    points: List[Optional[Tuple[int, int]]] = [None] * n_vertices  # noqa: TAE002
    for i in range(n_vertices):
        a, b = map(int, input().split())
        points[i] = (a, b)

    edges = []  # (start, end, weight)
    n_subsets = int(input())
    for i in range(n_vertices):
        (x0, y0) = points[i]  # type: ignore
        for j in range(i + 1, n_vertices):
            (x, y) = points[j]  # type: ignore
            distance = math.sqrt((x - x0) ** 2 + (y - y0) ** 2)
            edges.append((i, j, distance))

    min_d = min_distance_clustering(edges=edges, n=n_vertices, k=n_subsets)
    print("{0:.9f}".format(min_d))
