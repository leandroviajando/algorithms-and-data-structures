import sys
from typing import List

sys.setrecursionlimit(200000)


def explore(adj: List[List[int]], visited: List[bool], u: int) -> None:
    visited[u] = True
    for v in adj[u]:
        if not visited[v]:
            explore(adj, visited, v)


def topological_sort(adj: List[List[int]], visited: List[bool], stack: List[int], u: int) -> None:
    visited[u] = True
    for v in adj[u]:
        if not visited[v]:
            topological_sort(adj, visited, stack, v)
    stack.append(u)


def number_of_strongly_connected_components(adj: List[List[int]]) -> int:  # noqa: C901
    res = 0

    n = len(adj)
    visited = [False] * n
    stack: List[int] = []

    for u in range(n):
        if not visited[u]:
            topological_sort(adj, visited, stack, u)

    reverse_adj: List[List[int]] = [[] for _ in range(n)]
    for u in range(n):
        for v in adj[u]:
            reverse_adj[v].append(u)

    visited = [False] * n

    while stack:
        u = stack.pop()
        if not visited[u]:
            explore(reverse_adj, visited, u)
            res += 1

    return res


if __name__ == "__main__":
    n, m = map(int, input().split())

    edges = [tuple(map(int, input().split())) for _ in range(m)]
    adj: List[List[int]] = [[] for _ in range(n)]
    for a, b in edges:
        adj[a - 1].append(b - 1)

    print(number_of_strongly_connected_components(adj))
