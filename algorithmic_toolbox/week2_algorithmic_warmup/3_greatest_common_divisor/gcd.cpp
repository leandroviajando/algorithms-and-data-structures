#include <algorithm>
#include <iostream>

int gcd_naive(int a, int b) {
  int current_gcd = 1;

  for (int d = 2; d <= a && d <= b; d++)
    if (a % d == 0 && b % d == 0)
      if (d > current_gcd)
        current_gcd = d;

  return current_gcd;
}

int gcd_euclidean(int a, int b) {
  int min = std::min(a, b);
  int max = std::max(a, b);

  return min == 0 ? max : gcd_euclidean(max % min, min);
}

int main() {
  int a, b;
  std::cin >> a >> b;

  std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd_euclidean(a, b) << std::endl;

  return 0;
}
