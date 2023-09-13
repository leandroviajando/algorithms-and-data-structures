from trie_matching import solve


def test_solve() -> None:
    assert solve("AAA", 1, ["AA"]) == [0, 1]
    assert solve("AA", 1, ["T"]) == []
    assert solve("AATCGGGTTCAATCGGGGT", 2, ["ATCG", "GGGT"]) == [1, 4, 11, 15]
