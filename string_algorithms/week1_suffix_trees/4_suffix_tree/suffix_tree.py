from collections import deque
from typing import Dict, Optional


class Node:
    def __init__(self, label: Optional[str]) -> None:
        self.label = label
        self.outgoing_edges: Dict[str, Node] = {}


class SuffixTree:
    def __init__(self, s: str) -> None:  # noqa: C901
        self.root = Node(None)
        self.root.outgoing_edges[s[0]] = Node(s)

        for i in range(1, len(s)):
            cur = self.root
            j = i
            while j < len(s):
                if s[j] in cur.outgoing_edges:
                    child = cur.outgoing_edges[s[j]]
                    label = child.label or ""
                    k = j + 1
                    while k - j < len(label) and s[k] == label[k - j]:
                        k += 1
                    if k - j == len(label):
                        cur = child
                        j = k
                    else:
                        existing, new = label[k - j], s[k]
                        mid = Node(label[: k - j])
                        mid.outgoing_edges[new] = Node(s[k:])
                        child.label = label[k - j :]
                        mid.outgoing_edges[existing] = child
                        cur.outgoing_edges[s[j]] = mid
                else:
                    cur.outgoing_edges[s[j]] = Node(s[j:])

    def __str__(self) -> str:
        res = []
        dq: deque = deque()
        dq.append(self.root)
        while dq:
            u = dq.popleft()
            if u != self.root:
                res.append(u.label)
            dq.extend(u.outgoing_edges.values())
        return "\n".join(res)


if __name__ == "__main__":
    text = input()
    stree = SuffixTree(text)
    print(stree)
