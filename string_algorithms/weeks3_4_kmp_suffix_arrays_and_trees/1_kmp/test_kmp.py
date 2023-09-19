from kmp import find_pattern


def test_find_pattern() -> None:
    assert find_pattern(pattern="TACG", text="GT") == []
    assert find_pattern(pattern="ATA", text="ATATA") == [0, 2]
    assert find_pattern(pattern="ATAT", text="GATATATGCATATACTT") == [1, 3, 9]
