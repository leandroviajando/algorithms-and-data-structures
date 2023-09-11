import math
from typing import List


class Edge:
    def __init__(self, u: int, v: int, weight: float) -> None:
        self.u = u
        self.v = v
        self.weight = weight


def find_parent(parent: List[int], vertex: int) -> int:  # noqa: FNE008
    if parent[vertex] == -1:
        return vertex
    return find_parent(parent, parent[vertex])


def union_sets(parent: List[int], u: int, v: int) -> None:
    u_parent = find_parent(parent, u)
    v_parent = find_parent(parent, v)
    if u_parent != v_parent:
        parent[u_parent] = v_parent


def minimum_distance(x: List[int], y: List[int]) -> float:  # noqa: C901
    n = len(x)
    edges = []

    # Create edges from all pairs of points with their Euclidean distances as weights.
    for i in range(n):
        for j in range(i + 1, n):
            dist = math.sqrt((x[i] - x[j]) ** 2 + (y[i] - y[j]) ** 2)
            edges.append(Edge(i, j, dist))

    # Sort edges by weight in ascending order.
    edges.sort(key=lambda edge: edge.weight)

    # Initialize a disjoint-set (union-find) data structure.
    parent = [-1] * n

    result = 0.0
    for edge in edges:
        u = edge.u
        v = edge.v
        weight = edge.weight

        # Check if adding this edge does not create a cycle in the current spanning tree.
        if find_parent(parent, u) != find_parent(parent, v):
            result += weight
            union_sets(parent, u, v)

    return result


if __name__ == "__main__":
    n = int(input())
    x = []
    y = []

    for _ in range(n):
        xi, yi = map(int, input().split())
        x.append(xi)
        y.append(yi)

    print("{:.10f}".format(minimum_distance(x, y)))
