from typing import Dict, Final, List, Tuple

LETTERS: Final = ("$", "A", "C", "G", "T")


def preprocess_bwt(bwt: str) -> Tuple[Dict[str, int], Dict[str, List[int]]]:  # noqa: C901, FNE008, TAE002
    """
    Preprocess the Burrows-Wheeler Transform bwt of some text and compute as a result:
     * starts - for each character C in bwt, starts[C] is the first position
        of this character in the sorted array of all characters of the text.
     * occ_count_before - for each character C in bwt and each position P in bwt,
        occ_count_before[C][P] is the number of occurrences of character C in bwt
        from position 0 to position P inclusive.
    """
    freq = {char: 0 for char in LETTERS}
    for char in bwt:
        freq[char] += 1

    first_occur = {"$": 0}
    for i in range(1, len(LETTERS)):
        first_occur[LETTERS[i]] = first_occur[LETTERS[i - 1]] + freq[LETTERS[i - 1]]

    count = {letter: [0] * (len(bwt) + 1) for letter in LETTERS}
    for i in range(len(bwt)):
        tmp_dict = {bwt[i]: 1}
        for letter in LETTERS:
            count[letter][i + 1] = count[letter][i] + tmp_dict.get(letter, 0)

    return first_occur, count


def count_occurrences(bwt: str, pattern: str, starts: Dict[str, int], occ_counts_before: Dict[str, List[int]]) -> int:
    """
    Compute the number of occurrences of string pattern in the text
    given only Burrows-Wheeler Transform bwt of the text and additional
    information we get from the preprocessing stage - starts and occ_counts_before.
    """
    top = 0
    bottom = len(bwt) - 1

    while top <= bottom:
        if pattern:
            symbol = pattern[-1]
            pattern = pattern[:-1]

            top = starts[symbol] + occ_counts_before[symbol][top]
            bottom = starts[symbol] + occ_counts_before[symbol][bottom + 1] - 1
        else:
            return bottom - top + 1
    return 0


if __name__ == "__main__":
    bwt = input()
    n_patterns = int(input())
    patterns = input().split()
    first_occur, count = preprocess_bwt(bwt)
    for pattern in patterns:
        print(count_occurrences(bwt, pattern, first_occur, count), end=" ")
    print()
