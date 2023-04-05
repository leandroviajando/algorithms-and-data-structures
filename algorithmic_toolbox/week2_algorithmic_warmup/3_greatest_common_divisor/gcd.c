#include <stdio.h>

int gcd_naive(int a, int b) {
  int current_gcd = 1;

  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }

  return current_gcd;
}

int gcd_euclidean(int a, int b) {
  int min = a < b ? a : b;
  int max = a > b ? a : b;

  return min == 0 ? max : gcd_euclidean(max % min, min);
}

int main() {
  int a, b;
  int _ = scanf("%d %d", &a, &b);

  printf("%d\n", gcd_naive(a, b));
  printf("%d\n", gcd_euclidean(a, b));

  return 0;
}
