from typing import List

NA = -1


class Node:
    def __init__(self) -> None:
        self.next = [NA] * 4

    def is_leaf(self) -> bool:
        return all(x == NA for x in self.next)


def letter_to_index(letter: str) -> int:
    return 0 if letter == "A" else 1 if letter == "C" else 2 if letter == "G" else 3 if letter == "T" else -1


def build_trie(patterns: List[str]) -> List[Node]:  # noqa: C901
    trie = [Node()]

    for pattern in patterns:
        cur = 0

        for symbol in pattern:
            index = letter_to_index(symbol)

            if trie[cur].next[index] == -1:
                trie.append(Node())
                trie[cur].next[index] = len(trie) - 1

            cur = trie[cur].next[index]

    return trie


def solve(text: str, n: int, patterns: List[str]) -> List[int]:  # noqa: C901
    result = []
    trie = build_trie(patterns)

    for i in range(len(text)):
        cur = 0
        j = i

        while True:
            if trie[cur].is_leaf():
                result.append(i)
                break

            if j >= len(text):
                break

            index = letter_to_index(text[j])
            if trie[cur].next[index] != -1:
                cur = trie[cur].next[index]
                j += 1
            else:
                break

    return result


if __name__ == "__main__":
    text = input()
    n = int(input())
    patterns = [input() for _ in range(n)]

    ans = solve(text, n, patterns)

    for i in range(len(ans)):
        print(ans[i], end=" ")
    print()
