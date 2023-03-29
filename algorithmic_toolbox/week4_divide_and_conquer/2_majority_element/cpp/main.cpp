#include <iostream>
#include <vector>

#include "majority_element.hpp"

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i)
    std::cin >> a[i];

  std::cout << (get_majority_element(a, 0, a.size()) != -1) << std::endl;
}
