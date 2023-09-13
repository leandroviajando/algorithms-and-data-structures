from trie_matching_extended import solve


def test_solve() -> None:
    assert solve("AAA", 1, ["AA"]) == [0, 1]
    assert solve("ACATA", 3, ["AT", "A", "AG"]) == [0, 2, 4]
