import sys


def optimal_summands(n: int) -> list[int]:
    summands: list[int] = []

    for i in range(1, n + 1):
        if n - i > i:
            summands.append(i)
            n -= i
        else:
            summands.append(n)
            break

    return summands


if __name__ == "__main__":
    n = int(sys.stdin.read())
    summands = optimal_summands(n)
    print(len(summands))
    for x in summands:
        print(x, end=" ")
