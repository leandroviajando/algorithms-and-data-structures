#include <iostream>
#include <vector>

#include "max_pairwise_product.hpp"

int main() {
  int n;
  std::cin >> n;
  std::vector<long long> numbers(n);
  for (int i = 0; i < n; ++i)
    std::cin >> numbers[i];

  long long result = maxPairwiseProduct(numbers);
  std::cout << result << std::endl;
  return 0;
}
