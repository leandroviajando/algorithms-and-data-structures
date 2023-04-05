#include <iostream>

long long get_fibonacci_huge_naive(long long n, long long m) {
  if (n <= 1)
    return n;

  long long previous = 0;
  long long current = 1;

  for (long long i = 0; i < n - 1; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = (tmp_previous + current) % m;
  }

  return current;
}

long long get_pisano_period(long long m) {
  long long a = 0, b = 1, c = a + b;

  for (int i = 0; i < m * m; i++) {
    c = (a + b) % m;
    a = b;
    b = c;

    if (a == 0 && b == 1) return i + 1;
  }

  throw std::runtime_error("could not find pisano period");
}

long long get_fibonacci_huge(long long n, long long m) {
  return get_fibonacci_huge_naive(n % get_pisano_period(m), m);
}

int main() {
  long long n, m;
  std::cin >> n >> m;

  std::cout << get_fibonacci_huge(n, m) << std::endl;
  std::cout << get_fibonacci_huge_naive(n, m) << std::endl;

  return 0;
}
