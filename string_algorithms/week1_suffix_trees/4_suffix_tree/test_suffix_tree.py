from suffix_tree import SuffixTree


def test_suffix_tree() -> None:
    assert str(SuffixTree("A$")) == "A$\n$"
    assert str(SuffixTree("ACA$")) == "A\nCA$\n$\n$\nCA$"
    assert str(SuffixTree("ATAAATG$")) == "A\nT\nG$\n$\nA\nT\nG$\nAAATG$\nTG$\nATG$\nG$\nAAATG$"
