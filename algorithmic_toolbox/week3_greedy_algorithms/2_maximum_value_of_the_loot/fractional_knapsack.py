import sys
from typing import Sequence


def get_optimal_value(*, capacity: int, weights: Sequence[int], values: Sequence[int]) -> float:
    weight = 0
    value = 0.0

    for item in sorted(
        [{"weight": weight, "value": value, "unit-value": value / weight} for weight, value in zip(weights, values)],
        key=lambda item: item["unit-value"],
        reverse=True,
    ):
        if weight >= capacity:
            break

        weight += (units := int(min(item["weight"], capacity - weight)))
        value += units * item["unit-value"]

    return value


if __name__ == "__main__":
    data = list(map(int, sys.stdin.read().split()))
    n, capacity = data[0:2]
    values = data[2 : (2 * n + 2) : 2]
    weights = data[3 : (2 * n + 2) : 2]
    opt_value = get_optimal_value(capacity=capacity, weights=weights, values=values)
    print("{:.10f}".format(opt_value))
