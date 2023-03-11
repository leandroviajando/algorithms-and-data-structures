public class TestMaxPairwiseProduct {
  private static MaxPairwiseProduct maxPairwiseProduct = new MaxPairwiseProduct();

  public static void main(String[] args) {
    long[] numbers1 = { 5, 6, 7, 4, 2 };
    assert maxPairwiseProduct.getMaxPairwiseProduct(numbers1) == 6 * 7;

    long[] numbers2 = { 100000, 90000 };
    assert maxPairwiseProduct.getMaxPairwiseProduct(numbers2) == 100000 * 90000;
    System.out.println("All tests passed!");
  }
}
