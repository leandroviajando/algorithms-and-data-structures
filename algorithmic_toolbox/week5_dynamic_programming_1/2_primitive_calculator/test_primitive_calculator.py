from primitive_calculator import optimal_sequence


def test_optimal_sequence() -> None:
    assert list(optimal_sequence(1)) == [1]
    assert list(optimal_sequence(5)) in ([1, 2, 4, 5], [1, 3, 4, 5])
    assert list(optimal_sequence(10)) == [1, 3, 9, 10]
    assert list(optimal_sequence(96234)) == [1, 3, 9, 10, 11, 22, 66, 198, 594, 1782, 5346, 16038, 16039, 32078, 96234]
