import sys


class Solver:
    def __init__(self, s: str) -> None:
        self.s = s
        self.hash_values = [0] * (len(s) + 1)

        self.__pre_compute_hash_values()

    def __pre_compute_hash_values(self) -> None:
        prime = 31
        p_pow = 1

        for i in range(len(self.s)):
            self.hash_values[i + 1] = self.hash_values[i] + (ord(self.s[i]) - ord("a") + 1) * p_pow
            p_pow *= prime

    def __call__(self, a: int, b: int, length: int) -> bool:  # noqa: FNE005
        prime = 31
        hash_b = self.hash_values[b + length] - self.hash_values[b]
        hash_a = self.hash_values[a + length] - self.hash_values[a]

        return hash_b == hash_a * (prime ** (b - a))


if __name__ == "__main__":
    s = sys.stdin.readline().strip()
    q = int(sys.stdin.readline())

    solver = Solver(s)

    for _ in range(q):
        a, b, l = map(int, sys.stdin.readline().split())
        print("Yes" if solver(a, b, l) else "No")
