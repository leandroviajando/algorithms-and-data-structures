from typing import Sequence

import pytest
from lcs2 import lcs2


@pytest.mark.parametrize(
    ("a", "b", "count"),
    [
        ((2, 7, 5), (2, 5), 2),
        ([7], (1, 2, 3, 4), 0),
        ((2, 7, 8, 3), (5, 2, 8, 7), 2),
    ],
)
def test_lcs2(a: Sequence[int], b: Sequence[int], count: int) -> None:
    assert lcs2(a, b) == count
