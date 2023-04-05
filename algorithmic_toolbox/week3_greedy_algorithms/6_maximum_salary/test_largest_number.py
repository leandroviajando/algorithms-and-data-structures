from largest_number import largest_number


def test_largest_number() -> None:
    assert largest_number(("21", "2")) == "221"
    assert largest_number(("9", "4", "6", "1", "9")) == "99641"
    assert largest_number(("23", "39", "92")) == "923923"
