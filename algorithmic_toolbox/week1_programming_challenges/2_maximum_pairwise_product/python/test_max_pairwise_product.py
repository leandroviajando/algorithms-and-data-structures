from max_pairwise_product import max_pairwise_product


def test_max_pairwise_product() -> None:
    assert max_pairwise_product([5, 6, 7, 4, 2]) == 6 * 7, "should calculate max pairwise product"
    assert (
        max_pairwise_product([90_000, 100_000]) == 9_000_000_000
    ), "should calculate max pairwise product for large numbers"
