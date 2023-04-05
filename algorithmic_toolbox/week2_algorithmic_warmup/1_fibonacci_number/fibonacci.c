#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int fibonacci_naive(int n) {
  return n <= 1 ? n : fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

int fibonacci_fast(int n) {
  if (n <= 1) return n;

  long *fibNums = (long *)malloc((n + 1) * sizeof(long));
  fibNums[0] = 0;
  fibNums[1] = 1;

  for (int i = 2; i <= n; ++i)
    fibNums[i] = fibNums[i - 1] + fibNums[i - 2];

  int result = fibNums[n];
  free(fibNums);
  return result;
}

void test_solution() {
  assert(fibonacci_fast(3) == 2);
  assert(fibonacci_fast(10) == 55);
  for (int n = 0; n < 20; ++n) assert(fibonacci_fast(n) == fibonacci_naive(n));
}

int main() {
  int n = 0;
  int _ = scanf("%d", &n);

  printf("%d\n", fibonacci_naive(n));
  printf("%d\n", fibonacci_fast(n));
  test_solution();

  printf("OK\n");
  return 0;
}
