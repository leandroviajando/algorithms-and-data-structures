#include <iostream>
#include <vector>

#include "sorting.hpp"

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i)
    std::cin >> a[i];

  randomized_quick_sort(a, 0, a.size() - 1, true);
  for (size_t i = 0; i < a.size(); ++i)
    std::cout << a[i] << ' ';
}
