"""Tutorial: https://www.geeksforgeeks.org/closest-pair-of-points-using-divide-and-conquer-algorithm/"""

import math
import sys
from dataclasses import dataclass
from itertools import starmap
from typing import Sequence


@dataclass
class Point:
    x: int
    y: int


def dist(p1: Point, p2: Point) -> float:
    return math.sqrt(math.pow(p1.x - p2.x, 2) + math.pow(p1.y - p2.y, 2))


def brute_force(points: Sequence[Point]) -> float:  # noqa: C901
    min_dist = float("inf")

    for i in range(n := len(points)):
        for j in range(i + 1, n):
            if dist(points[i], points[j]) < min_dist:
                min_dist = dist(points[i], points[j])

    return min_dist


def strip_closest(strip: Sequence[Point], *, d: float) -> float:  # noqa: C901
    min_dist = d
    size = len(strip)
    strip = sorted(strip, key=lambda point: point.y)

    for i in range(size):
        for j in range(i + 1, size):
            if (strip[j].y - strip[i].y) >= min_dist:
                break
            if dist(strip[i], strip[j]) < min_dist:
                min_dist = dist(strip[i], strip[j])

    return min_dist


def _minimum_distance(points: Sequence[Point]) -> float:
    if (n := len(points)) <= 3:
        return brute_force(points)

    mid = n // 2
    mid_point = points[mid]

    dl = _minimum_distance(points[:mid])
    dr = _minimum_distance(points[mid:])
    d = min(dl, dr)

    strip = [points[i] for i in range(n) if abs(points[i].x - mid_point.x) < d]

    return min(d, strip_closest(strip, d=d))


def minimum_distance(x: Sequence[int], y: Sequence[int]) -> float:
    return _minimum_distance(
        sorted(
            starmap(Point, zip(x, y)),
            key=lambda point: point.x,
        )
    )


if __name__ == "__main__":
    data = list(map(int, sys.stdin.read().split()))
    n = data[0]
    x = data[1::2]
    y = data[2::2]
    print("{0:.9f}".format(minimum_distance(x, y)))
