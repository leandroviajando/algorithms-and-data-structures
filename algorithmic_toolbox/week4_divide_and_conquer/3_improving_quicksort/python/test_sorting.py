from sorting import randomized_quick_sort


def test_randomized_quick_sort() -> None:
    randomized_quick_sort(a := [2, 3, 9, 2, 2], 0, len(a) - 1, use_partition3=True)
    assert a == [2, 2, 2, 3, 9]
