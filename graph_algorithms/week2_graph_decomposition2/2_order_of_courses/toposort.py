from typing import List


def dfs(adj: List[List[int]], used: List[bool], order: List[int], v: int) -> None:
    used[v] = True

    for w in adj[v]:
        if not used[w]:
            dfs(adj, used, order, w)

    order.append(v)


def toposort(adj: List[List[int]]) -> List[int]:
    used = [False] * len(adj)
    order: List[int] = []

    for v in range(len(adj)):
        if not used[v]:
            dfs(adj, used, order, v)

    return list(reversed(order))


if __name__ == "__main__":  # noqa: C901
    n, m = map(int, input().split())

    edges = [tuple(map(int, input().split())) for _ in range(m)]
    adj: List[List[int]] = [[] for _ in range(n)]
    for a, b in edges:
        adj[a - 1].append(b - 1)

    order = toposort(adj)
    for x in order:
        print(x + 1, end=" ")
    print()
