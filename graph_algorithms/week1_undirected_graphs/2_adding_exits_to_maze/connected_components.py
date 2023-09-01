from typing import List


def explore(adj: List[List[int]], visited: List[bool], u: int) -> None:
    """Marks all vertices reachable from u as visited."""
    visited[u] = True

    for v in adj[u]:
        if not visited[v]:
            explore(adj, visited, v)


def number_of_components(adj: List[List[int]]) -> int:
    """Returns the number of connected components in the given undirected graph."""
    res = 0

    visited = [False] * len(adj)
    for u in range(len(adj)):
        if not visited[u]:
            explore(adj, visited, u)
            res += 1

    return res


if __name__ == "__main__":
    n, m = map(int, input().split())

    edges = [tuple(map(int, input().split())) for _ in range(m)]
    adj: List[List[int]] = [[] for _ in range(n)]
    for a, b in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)

    print(number_of_components(adj))
