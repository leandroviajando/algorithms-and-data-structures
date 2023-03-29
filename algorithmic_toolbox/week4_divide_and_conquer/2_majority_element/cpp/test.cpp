#include <cassert>
#include <iostream>
#include <vector>

#include "majority_element.hpp"

void test_majority_element() {
  std::vector<int> a = {2, 3, 9, 2, 2};
  assert(get_majority_element(a, 0, a.size()) == 2);

  std::vector<int> b = {1, 2, 3, 4};
  assert(get_majority_element(b, 0, b.size()) == -1);

  std::vector<int> c = {1, 2, 3, 1};
  assert(get_majority_element(c, 0, c.size()) == -1);
}

int main() {
  test_majority_element();
  std::cout << "All tests passed!" << std::endl;
  return 0;
}
