#include <iostream>

int get_change(int m) {
  int n = m % 10, o = n % 5;

  return m / 10 + n / 5 + o / 1;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << std::endl;
}
