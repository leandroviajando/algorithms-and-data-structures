#include <stdio.h>
#include <stdlib.h>

long long get_fibonacci_huge_naive(long long n, long long m) {
  if (n <= 1) {
    return n;
  }

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
  long long period = 0;

  for (long long i = 0; i < m * m; i++) {
    c = (a + b) % m;
    a = b;
    b = c;

    if (a == 0 && b == 1) {
      period = i + 1;
      break;
    }
  }

  return period;
}

long long get_fibonacci_huge(long long n, long long m) {
  long long pisano_period = get_pisano_period(m);
  long long remainder = n % pisano_period;
  return get_fibonacci_huge_naive(remainder, m);
}

int main() {
  long long n, m;
  int _ = scanf("%lld %lld", &n, &m);

  printf("%lld\n", get_fibonacci_huge(n, m));
  printf("%lld\n", get_fibonacci_huge_naive(n, m));

  return 0;
}
