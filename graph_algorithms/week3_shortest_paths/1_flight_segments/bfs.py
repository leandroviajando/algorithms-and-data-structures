from queue import Queue
from typing import List


def distance(adj: List[List[int]], s: int, t: int) -> int:  # noqa: C901
    dist = [-1] * len(adj)
    dist[s] = 0
    queue: Queue = Queue()
    queue.put(s)
    while dist[t] == -1 and not queue.empty():
        u = queue.get()
        for v in adj[u]:
            if dist[v] == -1:
                dist[v] = dist[u] + 1
                queue.put(v)
    return dist[t]


if __name__ == "__main__":
    n, m = list(map(int, input().split()))

    edges = [tuple(map(int, input().split())) for _ in range(m)]
    adj: List[List[int]] = [[] for _ in range(n)]
    for a, b in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)

    u, v = map(int, input().split())
    print(distance(adj, u - 1, v - 1))
