import itertools
import sys
from collections import namedtuple
from typing import Collection

Segment = namedtuple("Segment", "start end")


def optimal_points(segments: Collection[Segment]) -> Collection[int]:  # noqa: C901
    points = []

    segments = sorted(segments, key=lambda x: x.end)
    while segments:
        point = segments.pop(0).end
        points.append(point)

        for segment in segments.copy():
            if point in range(segment.start, segment.end + 1):
                segments.remove(segment)

    return points


if __name__ == "__main__":
    n, *data = map(int, sys.stdin.read().split())
    segments = [*itertools.starmap(Segment, zip(data[::2], data[1::2]))]
    points = optimal_points(segments)
    print(len(points))
    for p in points:
        print(p, end=" ")
