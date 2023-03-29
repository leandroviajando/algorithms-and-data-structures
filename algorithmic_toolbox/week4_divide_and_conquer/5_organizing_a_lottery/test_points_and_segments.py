from typing import Sequence, TypedDict

import pytest
from points_and_segments import fast_count_segments, naive_count_segments


class CountSegmentsTestCase(TypedDict):
    inputs: Sequence[Sequence[int]]
    expected: Sequence[int]


@pytest.fixture()
def test_cases() -> Sequence[CountSegmentsTestCase]:
    return [
        {"inputs": ([0, 7], [5, 10], [1, 6, 11]), "expected": [1, 0, 0]},
        {"inputs": ([0, -3, 7], [5, 2, 10], [1, 6]), "expected": [2, 0]},
        {"inputs": ([-10], [10], [-100, 100, 0]), "expected": [0, 0, 1]},
    ]


def test_naive_count_segments(test_cases: Sequence[CountSegmentsTestCase]) -> None:
    for test_case in test_cases:
        assert naive_count_segments(*test_case["inputs"]) == test_case["expected"]


def test_fast_count_segments(test_cases: Sequence[CountSegmentsTestCase]) -> None:
    for test_case in test_cases:
        assert fast_count_segments(*test_case["inputs"]) == test_case["expected"]
