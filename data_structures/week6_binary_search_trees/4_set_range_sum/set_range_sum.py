from sys import stdin
from typing import Any, Optional, Tuple


class Vertex:
    """Vertex of a splay tree"""

    def __init__(self, key: int, _sum: int, left: Any, right: Any, parent: Any) -> None:  # noqa: ANN401
        (self.key, self._sum, self.left, self.right, self.parent) = (key, _sum, left, right, parent)


def update(v: Vertex) -> None:  # noqa: C901
    if v is None:
        return
    v._sum = v.key + (v.left._sum if v.left is not None else 0) + (v.right._sum if v.right is not None else 0)
    if v.left is not None:
        v.left.parent = v
    if v.right is not None:
        v.right.parent = v


def small_rotation(v: Vertex) -> None:  # noqa: C901
    parent = v.parent
    if parent is None:
        return
    grandparent = v.parent.parent  # type: ignore
    if parent.left == v:
        m = v.right
        v.right = parent
        parent.left = m
    else:
        m = v.left
        v.left = parent
        parent.right = m
    update(parent)
    update(v)
    v.parent = grandparent
    if grandparent is not None:
        if grandparent.left == parent:
            grandparent.left = v
        else:
            grandparent.right = v


def big_rotation(v: Vertex) -> None:
    if v.parent.left == v and v.parent.parent.left == v.parent:  # type: ignore  # noqa: SIM114
        # Zig-zig
        small_rotation(v.parent)  # type: ignore
        small_rotation(v)
    elif v.parent.right == v and v.parent.parent.right == v.parent:  # type: ignore
        # Zig-zig
        small_rotation(v.parent)  # type: ignore
        small_rotation(v)
    else:
        # Zig-zag
        small_rotation(v)
        small_rotation(v)


def splay(v: Vertex) -> Optional[Vertex]:  # noqa: C901
    """Makes splay of the given vertex and makes it the new root."""
    if v is None:
        return None

    while v.parent is not None:
        if v.parent.parent is None:
            small_rotation(v)
            break
        big_rotation(v)

    return v


def find_vertex(root: Vertex, key: int) -> Tuple[Vertex, Vertex]:  # noqa: C901
    """
    Searches for the given key in the tree with the given root
    and calls splay for the deepest visited node after that.
    Returns pair of the result and the new root.
    If found, result is a pointer to the node with the given key.
    Otherwise, result is a pointer to the node with the smallest
    bigger key (next value in the order).
    If the key is bigger than all keys in the tree,
    then result is None.
    """
    v = root
    last: Vertex = root
    _next: Vertex = None  # type: ignore
    while v is not None:
        if v.key >= key and (not _next or v.key < _next.key):
            _next = v
        last = v
        if v.key == key:
            break
        if v.key < key:
            v = v.right  # type: ignore
        else:
            v = v.left  # type: ignore
    root = splay(last)  # type: ignore
    return (_next, root)


def split(root: Vertex, key: int) -> Tuple[Optional[Vertex], Optional[Vertex]]:
    (result, root) = find_vertex(root, key)
    if result is None:
        return (root, None)
    right = splay(result)
    left = right.left  # type: ignore
    right.left = None  # type: ignore
    if left is not None:
        left.parent = None
    update(left)  # type: ignore
    update(right)  # type: ignore
    return (left, right)


def merge(left: Optional[Vertex], right: Optional[Vertex]) -> Optional[Vertex]:  # noqa: C901
    if left is None:
        return right
    if right is None:
        return left
    while right.left is not None:  # type: ignore
        right = right.left  # type: ignore
    right = splay(right)  # type: ignore
    right.left = left  # type: ignore
    update(right)  # type: ignore
    return right


# Code that uses splay tree to solve the problem

root: Vertex = None  # type: ignore


def insert(x: int) -> None:
    global root
    (left, right) = split(root, x)
    new_vertex = None
    if right is None or right.key != x:
        new_vertex = Vertex(x, x, None, None, None)
    root = merge(merge(left, new_vertex), right)  # type: ignore


def erase(x: int) -> None:  # noqa: C901
    global root
    node = find_vertex(root, x)

    if node[0] is None or node[0].key != x:
        return

    left = node[0].left
    right = node[0].right

    if left is not None:
        left.parent = None

    if right is not None:
        right.parent = None

    root = merge(left, right)  # type: ignore


def find(x: int) -> bool:  # noqa: FNE005
    global root
    node = find_vertex(root, x)
    return node[0] is not None and node[0].key == x


def _sum(fr: int, to: int) -> int:
    global root
    (left, middle) = split(root, fr)
    (middle, right) = split(middle, to + 1)  # type: ignore

    # Merge the split parts back together
    root = merge(merge(left, middle), right)  # type: ignore

    # The _sum is stored in the middle node
    return middle._sum if middle is not None else 0


if __name__ == "__main__":  # noqa: C901
    MODULO = 1000000001
    n = int(stdin.readline())
    last_sum_result = 0
    for _ in range(n):
        line = stdin.readline().split()
        if line[0] == "+":
            x = int(line[1])
            insert((x + last_sum_result) % MODULO)
        elif line[0] == "-":
            x = int(line[1])
            erase((x + last_sum_result) % MODULO)
        elif line[0] == "?":
            x = int(line[1])
            print("Found" if find((x + last_sum_result) % MODULO) else "Not found")
        elif line[0] == "s":
            l = int(line[1])
            r = int(line[2])
            res = _sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO)
            print(res)
            last_sum_result = res % MODULO
