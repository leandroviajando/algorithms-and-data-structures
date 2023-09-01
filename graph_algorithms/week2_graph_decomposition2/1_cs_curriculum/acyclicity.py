from typing import List


def is_cyclic_dfs(
    adj: List[List[int]],
    visited: List[bool],
    visited_during_current_traversal: List[bool],
    v: int,
) -> bool:
    visited[v] = True
    visited_during_current_traversal[v] = True

    for w in adj[v]:
        if visited_during_current_traversal[w] or is_cyclic_dfs(adj, visited, visited_during_current_traversal, w):
            return True

    visited_during_current_traversal[v] = False  # Reset before next traversal
    return False


def acyclic(adj: List[List[int]]) -> int:
    """Returns 0 if the directed graph is acyclic, 1 otherwise."""
    n = len(adj)
    visited = [False] * n
    visited_during_current_traversal = [False] * n

    for v in range(n):
        if not visited[v] and is_cyclic_dfs(adj, visited, visited_during_current_traversal, v):
            return 1

    return 0


if __name__ == "__main__":
    n, m = map(int, input().split())

    edges = [tuple(map(int, input().split())) for _ in range(m)]
    adj: List[List[int]] = [[] for _ in range(n)]
    for a, b in edges:
        adj[a - 1].append(b - 1)

    print(acyclic(adj))
