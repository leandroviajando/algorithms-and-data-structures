from change import get_change


def test_get_change() -> None:
    assert get_change(2) == len([1, 1])
    assert get_change(28) == len([10, 10, 5, 1, 1, 1])
