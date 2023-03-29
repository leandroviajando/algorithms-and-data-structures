#include <stdio.h>

#include "binary_search.h"

int main() {
  int n;
  scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);

  int m;
  scanf("%d", &m);
  int b[m];
  for (int i = 0; i < m; ++i)
    scanf("%d", &b[i]);

  for (int i = 0; i < m; ++i)
    printf("%d ", binary_search(a, n, b[i]));

  return 0;
}
