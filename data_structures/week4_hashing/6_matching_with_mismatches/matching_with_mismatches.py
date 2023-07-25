import sys
from typing import List


def solve(k: int, text: str, pattern: str) -> List[int]:
    return []


if __name__ == "__main__":
    for line in sys.stdin.readlines():
        k, t, p = line.split()
        ans = solve(int(k), t, p)
        print(len(ans), *ans)
