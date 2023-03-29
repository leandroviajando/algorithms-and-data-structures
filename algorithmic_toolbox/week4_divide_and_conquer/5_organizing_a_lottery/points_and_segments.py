import sys
from typing import Sequence


def fast_count_segments(starts: Sequence[int], ends: Sequence[int], points: Sequence[int]) -> Sequence[int]:  # noqa: C901
    sorted_tuples = sorted([(s, "s") for s in starts] + [(e, "e") for e in ends] + [(p, "p") for p in points])

    count = 0

    counts = [0] * len(points)
    for tup in sorted_tuples:
        if tup[1] == "s":
            count += 1
        elif tup[1] == "e":
            count -= 1
        else:
            counts[points.index(tup[0])] = count

    return counts


def naive_count_segments(starts: Sequence[int], ends: Sequence[int], points: Sequence[int]) -> Sequence[int]:
    """
    counts = [0] * len(points)
    for i in range(len(points)):  # noqa
        for j in range(len(starts)):
            if starts[j] <= points[i] <= ends[j]:
                counts[i] += 1
    return counts
    """
    return [sum([int(starts[j] <= points[i] <= ends[j]) for j in range(len(starts))]) for i in range(len(points))]


if __name__ == "__main__":
    data = list(map(int, sys.stdin.read().split()))
    n = data[0]
    m = data[1]
    starts = data[2 : 2 * n + 2 : 2]
    ends = data[3 : 2 * n + 2 : 2]
    points = data[2 * n + 2 :]
    counts = fast_count_segments(starts, ends, points)
    for x in counts:
        print(x, end=" ")
