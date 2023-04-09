import sys

COINS = (1, 3, 4)


def get_change(m: int) -> int:
    dp = [m + 1] * (m + 1)

    for i in range(1, m + 1):
        dp[i] = (
            1 if i in COINS else min((dp[int(j)] for j in (i - coin for coin in COINS) if int(j) == j)) + 1  # noqa: FURB123
        )

    if dp[m] > m:
        raise Exception("something went wrong")

    return dp[m]


if __name__ == "__main__":
    m = int(sys.stdin.read())
    print(get_change(m))
