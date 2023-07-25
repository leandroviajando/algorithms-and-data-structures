from typing import List


class RabinKarp:
    def __init__(self, pattern: str, text: str) -> None:
        self._pattern = pattern
        self._text = text

        self._window = len(pattern)
        self._scan_bound = len(text) - len(pattern) + 1
        self._checksums: List[int] = []

    def checksum(self, s: str) -> int:
        """Returns the hash of the string."""
        return sum([ord(s[i]) for i in range(len(s))])

    def precompute_hashes(self) -> None:
        """Precomputes hash values for the whole possible pattern entries in the text."""
        self._checksums = [self.checksum(self._text[: self._window])]

        for i in range(1, self._scan_bound):
            old_hash = self._checksums[i - 1]
            left_l_hash = ord(self._text[i - 1])
            right_l_hash = ord(self._text[i + self._window - 1])

            ith_hash = old_hash - left_l_hash + right_l_hash
            self._checksums.append(ith_hash)

    def __call__(self) -> List[int]:  # noqa: C901
        """Returns all occurrences of the pattern in the text."""
        results = []

        pattern_checksum = self.checksum(self._pattern)
        self.precompute_hashes()
        for i in range(self._scan_bound):
            if pattern_checksum == self._checksums[i] and self._pattern == self._text[i : i + self._window]:
                results.append(i)

        return results


if __name__ == "__main__":
    pattern, text = input().rstrip(), input().rstrip()

    rk = RabinKarp(pattern, text)
    res = rk()

    print(" ".join(map(str, res)))
