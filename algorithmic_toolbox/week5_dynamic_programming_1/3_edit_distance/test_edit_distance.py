from edit_distance import edit_distance


def test_edit_distance() -> None:
    assert edit_distance("ab", "ab") == 0
    assert edit_distance("short", "ports") == 3
    assert edit_distance("editing", "distance") == 5
