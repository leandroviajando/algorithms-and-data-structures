from partition3 import partition3


def test_partition3() -> None:
    assert partition3((3, 3, 3, 3)) == 0
    assert partition3([30]) == 0
    assert partition3((1, 2, 3, 4, 5, 5, 7, 7, 8, 10, 12, 19, 25)) == 1
