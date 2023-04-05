#include <stdio.h>
#include <stdlib.h>

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
  long long sum = 0;

  long long current = 0;
  long long next = 1;

  for (long long i = 0; i <= to; ++i) {
    if (i >= from) sum += current;

    long long new_current = next;
    next = next + current;
    current = new_current;
  }

  return sum % 10;
}

const int PISANO_PERIOD = 60;

// The last digit of the numbers in the Fibonacci Sequence form a pattern that repeats after every 60th number.
// Source: https://www.goldennumber.net/fibonacci-60-repeating-pattern/
long long get_fibonacci_partial_sum(long long from, long long to) {
  long fibNums[PISANO_PERIOD + 1];
  fibNums[0] = 0;
  fibNums[1] = 1;

  for (int i = 2; i <= PISANO_PERIOD; ++i)
    fibNums[i] = fibNums[i - 1] + fibNums[i - 2];

  from %= PISANO_PERIOD;
  to %= PISANO_PERIOD;

  long long sum = 0;
  for (int j = from; j <= to; j++) {
    sum += fibNums[j % PISANO_PERIOD];
    sum %= 10;
  }

  return sum;
}

int main() {
  long long from, to;
  int _ = scanf("%lld %lld", &from, &to);

  printf("%lld\n", get_fibonacci_partial_sum(from, to));
  printf("%lld\n", get_fibonacci_partial_sum_naive(from, to));

  return 0;
}
