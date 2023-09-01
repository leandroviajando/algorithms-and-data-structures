from typing import List


def dfs(adj: List[List[int]], visited: List[bool], u: int, v: int) -> int:
    """Returns 1 if there is a path between u and v, 0 otherwise."""
    if u == v or v in adj[u]:
        return 1

    visited[u] = True

    return int(any(dfs(adj, visited, w, v) for w in adj[u] if not visited[w]))


def reach(adj: List[List[int]], u: int, v: int) -> int:
    """Returns 1 if there is a path between u and v, 0 otherwise."""
    visited = [False] * len(adj)
    return dfs(adj, visited, u, v)


if __name__ == "__main__":
    n, m = map(int, input().split())

    edges = [tuple(map(int, input().split())) for _ in range(m)]
    adj: List[List[int]] = [[] for _ in range(n)]
    for a, b in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)

    u, v = map(int, input().split())
    print(reach(adj, u - 1, v - 1))
