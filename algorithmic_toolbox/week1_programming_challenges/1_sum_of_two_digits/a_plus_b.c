#include <stdio.h>

int main(int argc, char *argv[]) {
  int a = 0;
  int b = 0;
  int sum = 0;
  int e = scanf("%d", &a);
  e = scanf("%d", &b);
  sum = a + b;
  printf("%d", sum);
  return 0;
}
