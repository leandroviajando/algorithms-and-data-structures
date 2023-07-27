import threading
from typing import List, Union


def is_bst(  # noqa: CFQ004, C901
    tree: List[List[int]],
    *,
    index: int = 0,
    min_value: Union[int, float] = float("-inf"),
    max_value: Union[int, float] = float("inf"),
) -> bool:
    if not tree:
        return True

    if index == -1:
        return True

    if tree[index][0] < min_value or tree[index][0] >= max_value:
        return False

    left_is_bst = is_bst(
        tree,
        index=tree[index][1],
        min_value=min_value,
        max_value=tree[index][0],
    )

    right_is_bst = is_bst(
        tree,
        index=tree[index][2],
        min_value=tree[index][0],
        max_value=max_value,
    )

    return left_is_bst and right_is_bst


def main() -> None:
    nodes = int(input().strip())
    tree = [list(map(int, input().strip().split())) for _ in range(nodes)]
    print("CORRECT" if is_bst(tree) else "INCORRECT")


if __name__ == "__main__":
    threading.Thread(target=main).start()
