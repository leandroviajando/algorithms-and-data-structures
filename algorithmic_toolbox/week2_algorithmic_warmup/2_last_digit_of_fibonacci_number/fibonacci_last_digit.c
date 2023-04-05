#include <stdio.h>

int get_fibonacci_last_digit_naive(int n) {
  if (n <= 1) return n;

  int previous = 0;
  int current = 1;

  for (int i = 0; i < n - 1; ++i) {
    int tmp_previous = previous;
    previous = current;
    current = tmp_previous + current;
  }

  return current % 10;
}

int get_fibonacci_last_digit_optimized(int n) {
  if (n <= 1) return n;

  int previous = 0;
  int current = 1;

  for (int i = 0; i < n - 1; ++i) {
    int tmp_previous = previous;
    previous = current;
    current = (tmp_previous + current) % 10;
  }

  return current;
}

int main() {
  int n;
  int _ = scanf("%d", &n);

  printf("%d\n", get_fibonacci_last_digit_naive(n));
  printf("%d\n", get_fibonacci_last_digit_optimized(n));

  return 0;
}
