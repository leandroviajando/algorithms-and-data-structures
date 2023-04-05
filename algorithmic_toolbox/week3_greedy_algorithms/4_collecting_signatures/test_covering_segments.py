from covering_segments import Segment, optimal_points


def test_optimal_points() -> None:
    assert optimal_points([Segment(1, 3), Segment(2, 5), Segment(3, 6)]) == [3]
    assert optimal_points([Segment(4, 7), Segment(1, 3), Segment(2, 5), Segment(5, 6)]) == [3, 6]
