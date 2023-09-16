from bwtinverse import bwtinverse


def test_bwtinverse() -> None:
    assert bwtinverse("AC$A") == "ACA$"
    assert bwtinverse("AGGGAA$") == "GAGAGA$"
