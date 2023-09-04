from typing import List


def negative_cycle(adj: List[List[int]], cost: List[List[int]]) -> int:  # noqa: C901
    n = len(adj)
    dist = [0] * n

    # Perform n iterations of relaxation.
    for _ in range(n):
        for u in range(n):
            for i in range(len(adj[u])):
                v = adj[u][i]

                if dist[v] > dist[u] + cost[u][i]:
                    dist[v] = dist[u] + cost[u][i]

    # Check for negative cycles.
    for u in range(n):
        for i in range(len(adj[u])):
            v = adj[u][i]

            if dist[v] > dist[u] + cost[u][i]:
                return 1

    return 0


if __name__ == "__main__":
    n, m = list(map(int, input().split()))

    edges = [tuple(map(int, input().split())) for _ in range(m)]
    adj: List[List[int]] = [[] for _ in range(n)]
    cost: List[List[int]] = [[] for _ in range(n)]
    for a, b, w in edges:
        adj[a - 1].append(b - 1)
        cost[a - 1].append(w)

    print(negative_cycle(adj, cost))
