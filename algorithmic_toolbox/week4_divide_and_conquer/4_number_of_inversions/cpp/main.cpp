#include <iostream>
#include <vector>

#include "inversions.hpp"

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++)
    std::cin >> a[i];

  std::vector<int> b(a.size());
  std::cout << getNumberOfInversions(a, b, 0, a.size()) << std::endl;
}
