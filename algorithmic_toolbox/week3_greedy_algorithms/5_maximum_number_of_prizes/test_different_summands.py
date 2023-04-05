from different_summands import optimal_summands


def test_optimal_summands() -> None:
    assert optimal_summands(2) == [2]
    assert optimal_summands(6) == [1, 2, 3]
    assert optimal_summands(8) == [1, 2, 5]
