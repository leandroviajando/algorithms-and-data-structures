#include <iostream>

int fibonacci_sum_naive(long long n) {
  if (n <= 1) return n;

  long long previous = 0, current = 1, sum = 1;

  for (long long i = 0; i < n - 1; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = tmp_previous + current;
    sum += current;
  }

  return sum % 10;
}

// The last digit of the numbers in the Fibonacci Sequence form a pattern that repeats after every 60th number.
// Source: https://www.goldennumber.net/fibonacci-60-repeating-pattern/
int fibonacci_sum(long long n) {
  return fibonacci_sum_naive(n % 60);
}

int main() {
  long long n = 0;
  std::cin >> n;

  std::cout << fibonacci_sum(n) << std::endl;
  std::cout << fibonacci_sum_naive(n) << std::endl;
}
