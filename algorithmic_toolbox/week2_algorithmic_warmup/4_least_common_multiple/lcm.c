#include <stdio.h>

int gcd(int a, int b) {
  int tmp;
  while (b != 0) {
    tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

long long lcm(int a, int b) {
  return ((long long)a * b) / gcd(a, b);
}

int main() {
  int a, b;
  int _ = scanf("%d%d", &a, &b);
  printf("%lld\n", lcm(a, b));
  return 0;
}
