#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

long long max_dot_product(int* a, int* b, size_t n) {
  qsort(a, n, sizeof(int), cmpfunc);
  qsort(b, n, sizeof(int), cmpfunc);

  long long result = 0;
  for (size_t i = 0; i < n; i++) result += ((long long)a[i]) * b[i];

  return result;
}

int main() {
  size_t n;
  int _ = scanf("%zu", &n);
  int* a = malloc(n * sizeof(int));
  int* b = malloc(n * sizeof(int));
  for (size_t i = 0; i < n; i++) {
    int _ = scanf("%d", &a[i]);
  }
  for (size_t i = 0; i < n; i++) {
    int _ = scanf("%d", &b[i]);
  }
  printf("%lld\n", max_dot_product(a, b, n));
  free(a);
  free(b);
  return 0;
}
