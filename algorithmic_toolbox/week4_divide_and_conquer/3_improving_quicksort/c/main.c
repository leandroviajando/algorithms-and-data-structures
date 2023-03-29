#include <stdio.h>

#include "sorting.h"

int main() {
  int n;
  int _ = ("%d", &n);
  int *a = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    _ = scanf("%d", &a[i]);

  randomized_quick_sort(a, 0, n - 1, 1);
  for (int i = 0; i < n; i++)
    printf("%d ", a[i]);

  free(a);
  return 0;
}
