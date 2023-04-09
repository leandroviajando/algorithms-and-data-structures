from typing import Sequence

import pytest
from knapsack import optimal_weight


@pytest.mark.parametrize(
    ("W", "w", "expected"),
    [
        (1, (5, 7, 12, 18), 0),
        (2, (5, 7, 12, 18), 0),
        (3, (5, 7, 12, 18), 0),
        (4, (5, 7, 12, 18), 0),
        (5, (5, 7, 12, 18), 5),
        (6, (5, 7, 12, 18), 5),
        (7, (5, 7, 12, 18), 7),
        (8, (5, 7, 12, 18), 7),
        (9, (5, 7, 12, 18), 7),
        (10, (5, 7, 12, 18), 7),
        (11, (5, 7, 12, 18), 7),
        (12, (5, 7, 12, 18), 12),
        (13, (5, 7, 12, 18), 12),
        (14, (5, 7, 12, 18), 12),
        (15, (5, 7, 12, 18), 12),
        (16, (5, 7, 12, 18), 12),
        (17, (5, 7, 12, 18), 17),
        (18, (5, 7, 12, 18), 18),
        (19, (5, 7, 12, 18), 19),
    ],
)
def test_optimal_weight(W: int, w: Sequence[int], expected: int) -> None:  # noqa: N803
    assert optimal_weight(W, w) == expected
