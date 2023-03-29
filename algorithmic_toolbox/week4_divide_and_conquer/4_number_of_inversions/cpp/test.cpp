#include <cassert>
#include <iostream>
#include <vector>

#include "inversions.hpp"

void test_getNumberOfInversions() {
  std::vector<int> a = {2, 3, 9, 2, 9};
  std::vector<int> b(a.size());
  assert(getNumberOfInversions(a, b, 0, a.size()) == 2);
}

int main() {
  test_getNumberOfInversions();
  std::cout << "All tests passed!" << std::endl;
  return 0;
}
