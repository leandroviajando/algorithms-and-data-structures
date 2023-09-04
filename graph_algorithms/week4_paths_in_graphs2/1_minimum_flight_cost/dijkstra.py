from queue import PriorityQueue
from typing import List


def distance(adj: List[List[int]], cost: List[List[int]], s: int, t: int) -> int:  # noqa: C901
    dist: List[int] = [float("inf")] * len(adj)  # type: ignore
    prev = [-1] * len(adj)
    visited = [False] * len(adj)
    dist[s] = 0
    pq: PriorityQueue = PriorityQueue()
    pq.put((0, s))

    while not pq.empty():
        u = pq.get()[1]

        if not visited[u]:
            visited[u] = True
            for i in range(len(adj[u])):
                v = adj[u][i]
                if dist[v] > dist[u] + cost[u][i]:
                    dist[v] = dist[u] + cost[u][i]
                    prev[v] = u
                    pq.put((-dist[v], v))

    return dist[t] if dist[t] != float("inf") else -1


if __name__ == "__main__":
    n, m = list(map(int, input().split()))

    edges = [tuple(map(int, input().split())) for _ in range(m)]
    adj: List[List[int]] = [[] for _ in range(n)]
    cost: List[List[int]] = [[] for _ in range(n)]
    for a, b, w in edges:
        adj[a - 1].append(b - 1)
        cost[a - 1].append(w)

    u, v = map(int, input().split())
    print(distance(adj, cost, u - 1, v - 1))
