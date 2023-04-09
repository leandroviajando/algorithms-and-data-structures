from typing import Sequence

import pytest
from lcs3 import lcs3


@pytest.mark.parametrize(
    ("a", "b", "c", "count"),
    [
        ((1, 2, 3), (2, 1, 3), (1, 3, 5), 2),
        ((8, 3, 2, 1, 7), (8, 2, 1, 3, 8, 10, 7), (6, 8, 3, 1, 4, 7), 3),
    ],
)
def test_lcs3(a: Sequence[int], b: Sequence[int], c: Sequence[int], count: int) -> None:
    assert lcs3(a, b, c) == count
