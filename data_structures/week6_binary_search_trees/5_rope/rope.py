import sys


class Rope:
    def __init__(self, s: str) -> None:
        self.s = s

    def __str__(self) -> str:
        return self.s

    def process(self, i: int, j: int, k: int) -> None:
        # Replace this code with a faster implementation
        t = self.s[:i] + self.s[j + 1 :]
        self.s = t[:k] + self.s[i : j + 1] + t[k:]


if __name__ == "__main__":
    rope = Rope(sys.stdin.readline().strip())
    q = int(sys.stdin.readline())
    for _ in range(q):
        rope.process(*map(int, sys.stdin.readline().strip().split()))
    print(rope)
