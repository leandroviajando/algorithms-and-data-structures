from is_bst import is_bst


def test_is_bst() -> None:
    assert is_bst([[2, 1, 2], [1, -1, -1], [3, -1, -1]]) is True
    assert is_bst([[1, 1, 2], [2, -1, -1], [3, -1, -1]]) is False
    assert is_bst([[2, 1, 2], [1, -1, -1], [2, -1, -1]]) is True
    assert is_bst([[2, 1, 2], [2, -1, -1], [3, -1, -1]]) is False
    assert is_bst([]) is True
    assert is_bst([[2147483647, -1, -1]]) is True
    assert is_bst([[1, -1, 1], [2, -1, 2], [3, -1, 3], [4, -1, 4], [5, -1, -1]]) is True
    assert is_bst([[4, 1, 2], [2, 3, 4], [6, 5, 6], [1, -1, -1], [3, -1, -1], [5, -1, -1], [7, -1, -1]]) is True
