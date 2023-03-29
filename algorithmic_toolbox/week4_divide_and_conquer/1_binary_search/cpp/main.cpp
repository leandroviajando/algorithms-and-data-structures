#include <iostream>
#include <vector>

#include "binary_search.hpp"

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++)
    std::cin >> a[i];

  int m;
  std::cin >> m;
  std::vector<int> b(m);
  for (int i = 0; i < m; ++i)
    std::cin >> b[i];

  for (int i = 0; i < m; ++i)
    std::cout << binary_search(a, b[i]) << ' ';
}
