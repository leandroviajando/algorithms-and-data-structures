from bwt import bwt


def test_bwt() -> None:
    assert bwt("AA$") == "AA$"
    assert bwt("ACACACAC$") == "CCCC$AAAA"
    assert bwt("AGACATA$") == "ATG$CAAA"
