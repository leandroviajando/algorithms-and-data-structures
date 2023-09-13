from trie import build_trie


def test_build_trie() -> None:
    assert build_trie(["ATA"]) == {0: {"A": 1}, 1: {"T": 2}, 2: {"A": 3}}
    assert build_trie(["AT", "AG", "AC"]) == {0: {"A": 1}, 1: {"T": 2, "G": 3, "C": 4}}
    assert build_trie(["ATAGA", "ATC", "GAT"]) == {
        0: {"A": 1, "G": 7},
        1: {"T": 2},
        2: {"A": 3, "C": 6},
        3: {"G": 4},
        4: {"A": 5},
        7: {"A": 8},
        8: {"T": 9},
    }
