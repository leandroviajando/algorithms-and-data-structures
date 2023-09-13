import sys
from typing import Dict, List


def build_trie(patterns: List[str]) -> Dict[int, Dict[str, int]]:  # noqa: C901
    tree: Dict[int, Dict[str, int]] = {}
    node_count = 1

    for pattern in patterns:
        current_node = 0

        for symbol in pattern:
            if current_node not in tree:
                tree[current_node] = {}

            if symbol in tree[current_node]:
                current_node = tree[current_node][symbol]
            else:
                tree[current_node][symbol] = node_count
                current_node = node_count
                node_count += 1

    return tree


if __name__ == "__main__":  # noqa: C901
    patterns = sys.stdin.read().split()[1:]
    tree = build_trie(patterns)
    for node in tree:
        for c in tree[node]:
            print("{}->{}:{}".format(node, tree[node][c], c))
