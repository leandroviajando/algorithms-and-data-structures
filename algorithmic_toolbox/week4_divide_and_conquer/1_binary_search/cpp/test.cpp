#include <cassert>
#include <iostream>
#include <vector>

#include "binary_search.hpp"

void test_binary_search() {
  std::vector<int> a = {1, 5, 8, 12, 13};
  assert(binary_search(a, 8) == 2);
  assert(binary_search(a, 1) == 0);
  assert(binary_search(a, 23) == -1);
  assert(binary_search(a, 1) == 0);
  assert(binary_search(a, 11) == -1);
  assert(binary_search(a, 13) == 4);

  std::vector<int> b = {1, 2, 3, 4, 5};
  assert(binary_search(b, 1) == 0);
  assert(binary_search(b, 2) == 1);
  assert(binary_search(b, 3) == 2);
  assert(binary_search(b, 4) == 3);
  assert(binary_search(b, 5) == 4);
  assert(binary_search(b, 6) == -1);
}

int main() {
  test_binary_search();
  std::cout << "All tests passed!" << std::endl;
  return 0;
}
