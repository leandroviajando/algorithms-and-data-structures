from closest import minimum_distance


def test_minimum_distance() -> None:
    assert minimum_distance([0, 3], [0, 4]) == 5.0
    assert minimum_distance([7, 1, 4, 7], [7, 100, 8, 7]) == 0.0
    assert (
        minimum_distance([4, -2, -3, -1, 2, -4, 1, -1, 3, -4, -2], [4, -2, -4, 3, 3, 0, 1, -1, -1, 2, 4])
        == 1.4142135623730951
    )
