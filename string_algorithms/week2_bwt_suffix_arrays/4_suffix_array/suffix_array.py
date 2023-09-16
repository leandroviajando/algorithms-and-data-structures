from typing import List


def build_suffix_array(text: str) -> List[int]:
    """
    Build suffix array of the string text and
    return a list result of the same length as the text
    such that the value result[i] is the index (0-based)
    in text where the i-th lexicographically smallest
    suffix of text starts.
    """
    sorted_suffixes = sorted([(text[i:], i) for i in range(len(text))])
    return [i for _, i in sorted_suffixes]


if __name__ == "__main__":
    text = input()
    print(" ".join(map(str, build_suffix_array(text))))
