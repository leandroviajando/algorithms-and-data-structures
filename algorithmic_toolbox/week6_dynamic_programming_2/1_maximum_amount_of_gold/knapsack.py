import sys
from typing import Sequence


def optimal_weight(W: int, w: Sequence[int]) -> int:  # noqa: N803
    dp = [0] * (W + 1)

    for i in range(len(w)):
        for j in range(W, w[i] - 1, -1):
            dp[j] = max(dp[j], dp[j - w[i]] + w[i])

    return dp[W]


if __name__ == "__main__":
    W, n, *w = list(map(int, sys.stdin.read().split()))
    print(optimal_weight(W, w))
