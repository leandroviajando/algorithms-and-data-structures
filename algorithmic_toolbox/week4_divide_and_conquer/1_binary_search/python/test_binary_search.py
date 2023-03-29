from binary_search import binary_search


def test_binary_search() -> None:
    assert binary_search([1, 5, 8, 12, 13], 8) == 2
    assert binary_search([1, 5, 8, 12, 13], 1) == 0
    assert binary_search([1, 5, 8, 12, 13], 23) == -1
    assert binary_search([1, 5, 8, 12, 13], 1) == 0
    assert binary_search([1, 5, 8, 12, 13], 11) == -1

    assert binary_search([1, 2, 3, 4, 5], 1) == 0
    assert binary_search([1, 2, 3, 4, 5], 2) == 1
    assert binary_search([1, 2, 3, 4, 5], 3) == 2
    assert binary_search([1, 2, 3, 4, 5], 4) == 3
    assert binary_search([1, 2, 3, 4, 5], 5) == 4
