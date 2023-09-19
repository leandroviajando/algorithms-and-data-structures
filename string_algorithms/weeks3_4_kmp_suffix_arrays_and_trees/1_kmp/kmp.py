from typing import List


def compute_prefix_function(pattern: str) -> List[int]:  # noqa: C901
    s = [0] * len(pattern)
    border = 0

    for i in range(1, len(pattern)):
        while border > 0 and pattern[i] != pattern[border]:
            border = s[border - 1]

        if pattern[i] == pattern[border]:
            border += 1
        else:
            border = 0

        s[i] = border

    return s


def find_pattern(*, pattern: str, text: str) -> List[int]:  # noqa: FNE008
    """
    Find all the occurrences of the pattern in the text
    and return a list of all positions in the text
    where the pattern starts in the text.
    """
    S = pattern + "$" + text  # noqa: N806
    s = compute_prefix_function(S)

    return [i - 2 * len(pattern) for i in range(len(pattern) + 1, len(S)) if s[i] == len(pattern)]


if __name__ == "__main__":
    pattern, text = input(), input()
    result = find_pattern(pattern=pattern, text=text)
    print(" ".join(map(str, result)))
