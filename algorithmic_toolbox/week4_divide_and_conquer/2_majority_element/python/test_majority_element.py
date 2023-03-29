from majority_element import get_majority_element


def test_get_majority_element() -> None:
    assert get_majority_element([2, 3, 9, 2, 2], 0, 5) == 2
    assert get_majority_element([1, 2, 3, 4], 0, 4) == -1
    assert get_majority_element([1, 2, 3, 1], 0, 4) == -1
