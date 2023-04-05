#include <cassert>
#include <iostream>
#include <vector>

int fibonacci_naive(int n) {
  return n <= 1 ? n : fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

int fibonacci_fast(int n) {
  if (n <= 1) return n;

  std::vector<long> fibNums(n + 1);
  fibNums[0] = 0;
  fibNums[1] = 1;

  for (int i = 2; i <= n; ++i)
    fibNums[i] = fibNums[i - 1] + fibNums[i - 2];

  return fibNums[n];
}

void test_solution() {
  assert(fibonacci_fast(3) == 2);
  assert(fibonacci_fast(10) == 55);
  for (int n = 0; n < 20; ++n) assert(fibonacci_fast(n) == fibonacci_naive(n));
}

int main() {
  int n = 0;
  std::cin >> n;

  std::cout << fibonacci_naive(n) << std::endl;
  std::cout << fibonacci_fast(n) << std::endl;
  test_solution();

  std::cout << "OK" << std::endl;
  return 0;
}
