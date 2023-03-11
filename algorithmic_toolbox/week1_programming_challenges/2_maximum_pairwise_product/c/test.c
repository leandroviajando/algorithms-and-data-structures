#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "max_pairwise_product.h"

void test_maxPairwiseProduct() {
  int64_t numbers1[] = {5, 6, 7, 4, 2};
  assert(maxPairwiseProduct(numbers1, 5) == 6 * 7);

  int64_t numbers2[] = {90000, 100000};
  assert(maxPairwiseProduct(numbers2, 2) == 9000000000);
}

int main() {
  test_maxPairwiseProduct();
  printf("All tests passed successfully.\n");
  return 0;
}
