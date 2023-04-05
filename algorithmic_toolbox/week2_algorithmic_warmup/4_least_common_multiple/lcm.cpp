#include <algorithm>
#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long)a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long)a * b;
}

int gcd(int a, int b) {
  int min = std::min(a, b);
  int max = std::max(a, b);

  return min == 0 ? max : gcd(max % min, min);
}

long long lcm(int a, int b) {
  return (long long)a * b / gcd(a, b);
}

int main() {
  int a, b;
  std::cin >> a >> b;

  std::cout << lcm(a, b) << std::endl;
  std::cout << lcm_naive(a, b) << std::endl;

  return 0;
}
