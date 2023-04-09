from typing import Sequence


def edit_distance(s: Sequence, t: Sequence) -> int:  # noqa: C901
    """Levenshtein distance: insertion, deletion, substitution"""

    if s == t:
        return 0

    m, n = len(s), len(t)
    dp = [[0 for _ in range(n + 1)] for _ in range(m + 1)]

    for i in range(m + 1):
        dp[i][0] = i

    for j in range(n + 1):
        dp[0][j] = j

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s[i - 1] == t[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1

    return dp[m][n]


if __name__ == "__main__":
    print(edit_distance(input(), input()))
