#include <stdio.h>
#include <stdlib.h>

#include "inversions.h"

int main() {
  int n;
  int _ = scanf("%d", &n);
  int a[n];
  for (size_t i = 0; i < n; i++)
    _ = scanf("%d", &a[i]);

  int b[n];
  printf("%lld\n", getNumberOfInversions(a, b, 0, n));
  return 0;
}
