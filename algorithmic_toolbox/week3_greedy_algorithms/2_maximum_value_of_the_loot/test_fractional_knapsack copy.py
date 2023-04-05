import math

from fractional_knapsack import get_optimal_value


def test_get_optimal_value() -> None:
    assert math.isclose(get_optimal_value(capacity=50, weights=(20, 50, 30), values=(60, 100, 120)), 180.0)
    assert math.isclose(get_optimal_value(capacity=10, weights=[30], values=[500]), 166.66666666666666)
