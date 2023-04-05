#include <stdio.h>

int get_change(int m) {
  int n = m % 10, o = n % 5;

  return m / 10 + n / 5 + o / 1;
}

int main() {
  int m;
  int _ = scanf("%d", &m);
  printf("%d\n", get_change(m));
  return 0;
}
