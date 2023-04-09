import sys
from typing import Sequence


def lcs2(a: Sequence, b: Sequence) -> int:  # noqa: C901
    """Longest common subsequence: insertion, deletion; no substitution"""

    if not set(a) & set(b):
        return 0

    m, n = len(a), len(b)
    dp = [[0 for _ in range(n + 1)] for _ in range(m + 1)]

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if a[i - 1] == b[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    return dp[m][n]


if __name__ == "__main__":
    data = list(map(int, sys.stdin.read().split()))

    n = data[0]
    data = data[1:]
    a = data[:n]

    data = data[n:]
    m = data[0]
    data = data[1:]
    b = data[:m]

    print(lcs2(a, b))
