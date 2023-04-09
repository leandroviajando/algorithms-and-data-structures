import sys
from typing import Sequence


def lcs3(a: Sequence, b: Sequence, c: Sequence) -> int:  # noqa: C901
    """Longest common subsequence: insertion, deletion; no substitution"""

    if not set(a) & set(b) & set(c):
        return 0

    m, n, o = len(a), len(b), len(c)
    dp = [[[0 for _ in range(o + 1)] for _ in range(n + 1)] for _ in range(m + 1)]

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            for k in range(1, o + 1):
                if a[i - 1] == b[j - 1] == c[k - 1]:
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1
                else:
                    dp[i][j][k] = max(dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1])

    return dp[m][n][o]


if __name__ == "__main__":
    data = list(map(int, sys.stdin.read().split()))
    an = data[0]
    data = data[1:]
    a = data[:an]
    data = data[an:]
    bn = data[0]
    data = data[1:]
    b = data[:bn]
    data = data[bn:]
    cn = data[0]
    data = data[1:]
    c = data[:cn]
    print(lcs3(a, b, c))
