#include <cassert>
#include <iostream>
#include <vector>

#include "sorting.hpp"

void test_randomized_quick_sort() {
  std::vector<int> a = {2, 3, 9, 2, 2};
  randomized_quick_sort(a, 0, a.size() - 1, true);
  assert(a == std::vector<int>({2, 2, 2, 3, 9}));
}

int main() {
  test_randomized_quick_sort();
  std::cout << "All tests passed!" << std::endl;
  return 0;
}
