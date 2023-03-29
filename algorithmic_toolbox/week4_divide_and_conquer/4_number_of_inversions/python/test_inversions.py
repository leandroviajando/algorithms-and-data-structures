from inversions import get_number_of_inversions


def test_get_number_of_inversions() -> None:
    assert get_number_of_inversions([2, 3, 9, 2, 9], [0, 0, 0, 0, 0], 0, 5) == 2
