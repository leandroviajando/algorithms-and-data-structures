import sys
from collections import namedtuple

Answer = namedtuple("Answer", "i j len")


def solve(s: str, t: str) -> Answer:  # noqa: C901
    ans = Answer(0, 0, 0)

    for i in range(len(s)):
        for j in range(len(t)):
            for l in range(min(len(s) - i, len(t) - j) + 1):
                if (l > ans.len) and (s[i : i + l] == t[j : j + l]):
                    ans = Answer(i, j, l)

    return ans


if __name__ == "__main__":
    for line in sys.stdin.readlines():
        s, t = line.split()

        ans = solve(s, t)

        print(ans.i, ans.j, ans.len)
