from suffix_array import build_suffix_array


def test_build_suffix_array() -> None:
    assert build_suffix_array("GAC$") == [3, 1, 2, 0]
    assert build_suffix_array("GAGAGAGA$") == [8, 7, 5, 3, 1, 6, 4, 2, 0]
    assert build_suffix_array("AACGATAGCGGTAGA$") == [15, 14, 0, 1, 12, 6, 4, 2, 8, 13, 3, 7, 9, 10, 11, 5]
