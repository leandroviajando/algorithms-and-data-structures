from queue import Queue
from typing import List


def bipartite(adj: List[List[int]]) -> int:  # noqa: C901
    colour = [-1] * len(adj)
    colour[0] = 0
    queue: Queue = Queue()
    queue.put(0)
    while not queue.empty():
        u = queue.get()
        for v in adj[u]:
            if colour[v] == -1:
                colour[v] = 1 - colour[u]
                queue.put(v)
            elif colour[v] == colour[u]:
                return 0
    return 1


if __name__ == "__main__":
    n, m = list(map(int, input().split()))

    edges = [tuple(map(int, input().split())) for _ in range(m)]
    adj: List[List[int]] = [[] for _ in range(n)]
    for a, b in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)

    print(bipartite(adj))
