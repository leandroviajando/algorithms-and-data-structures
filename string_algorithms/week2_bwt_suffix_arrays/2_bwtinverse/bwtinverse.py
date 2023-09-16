from typing import Final, List

LETTERS: Final = ["$", "A", "C", "G", "T"]


def map_last_col_to_first_col(bwt: str) -> List[int]:  # noqa: C901
    counts = {char: 0 for char in LETTERS}
    for char in bwt:
        counts[char] += 1

    total_count = -1
    position = {}
    for letter in LETTERS:
        total_count += counts[letter]
        position[letter] = total_count

    array = [0] * len(bwt)
    for i in range(len(bwt) - 1, -1, -1):
        array[i] = position[bwt[i]]
        position[bwt[i]] -= 1

    return array


def bwtinverse(bwt: str) -> str:
    last_to_first = map_last_col_to_first_col(bwt)

    result = ["$"] * len(bwt)
    pos = 0
    for i in range(1, len(bwt)):
        result[-(i + 1)] = bwt[pos]
        pos = last_to_first[pos]

    return "".join(result)


if __name__ == "__main__":
    bwt = input()
    print(bwtinverse(bwt))
