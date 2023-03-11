#include <stdint.h>
#include <stdio.h>

#include "max_pairwise_product.h"

int main() {
  int n;
  scanf("%d", &n);
  int64_t numbers[n];
  for (int i = 0; i < n; ++i) scanf("%ld", &numbers[i]);

  int64_t result = maxPairwiseProduct(numbers, n);
  printf("%ld", result);
  return 0;
}
