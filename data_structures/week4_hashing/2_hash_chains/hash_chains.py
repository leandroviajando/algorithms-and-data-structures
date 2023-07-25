from typing import List


class QueryProcessor:
    _multiplier = 263
    _prime = 1000000007

    def __init__(self, bucket_count: int) -> None:
        self.bucket_count = bucket_count
        self.buckets: List[List[str]] = [[] for _ in range(bucket_count)]

    def _hash_func(self, s: str) -> int:
        ans = 0
        for c in reversed(s):
            ans = (ans * self._multiplier + ord(c)) % self._prime
        return ans % self.bucket_count

    def add(self, s: str) -> None:
        """Insert s into the table.

        If there is already such string in the hash table, then the query is ignored.
        """
        hashed = self._hash_func(s)
        bucket = self.buckets[hashed]

        if s not in bucket:
            self.buckets[hashed] = [s] + bucket

    def delete(self, s: str) -> None:
        """Removes s from the table.

        If there is no such string in the hash table, then the query is ignored.
        """
        hashed = self._hash_func(s)

        bucket = self.buckets[hashed]
        for i in range(len(bucket)):
            if bucket[i] == s:
                bucket.pop(i)
                break

    def find(self, s: str) -> str:
        """Looks for s in the table.

        Returns “yes” or “no” depending on whether the table contains s or not.
        """
        hashed = self._hash_func(s)

        if s in self.buckets[hashed]:
            return "yes"

        return "no"

    def check(self, i: int) -> List[str]:
        """Returns the content of the i-th list in the table."""
        return self.buckets[i]

    def __call__(self, *, queries: List[str]) -> None:  # noqa: C901
        for query in queries:
            command, arg = query.split()

            if command == "add":
                self.add(arg)
            elif command == "del":
                self.delete(arg)
            elif command == "find":
                print(self.find(arg))
            elif command == "check":
                print(" ".join(self.check(int(arg))))


if __name__ == "__main__":
    bucket_count = int(input())
    n = int(input())

    qp = QueryProcessor(bucket_count)
    qp(queries=[input() for _ in range(n)])
