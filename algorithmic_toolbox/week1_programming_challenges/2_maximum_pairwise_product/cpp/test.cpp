#include <cassert>
#include <iostream>
#include <vector>

#include "max_pairwise_product.hpp"

void testMaxPairwiseProduct() {
  std::vector<long long> numbers1{5, 6, 7, 4, 2};
  assert(maxPairwiseProduct(numbers1) == 6 * 7);

  std::vector<long long> numbers2{100000, 90000};
  assert(maxPairwiseProduct(numbers2) == 9000000000);
}

int main() {
  testMaxPairwiseProduct();
  std::cout << "All tests passed!" << std::endl;
  return 0;
}
