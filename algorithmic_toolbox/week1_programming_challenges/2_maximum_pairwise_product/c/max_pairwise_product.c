#include "max_pairwise_product.h"

#include <stdint.h>
#include <stdio.h>

int64_t maxPairwiseProduct(const int64_t numbers[], int n) {
  int index1 = 0;
  for (int i = 1; i < n; i++)
    if (numbers[i] > numbers[index1])
      index1 = i;

  int index2 = index1 != 0 ? 0 : 1;
  for (int i = 1; i < n; i++)
    if (i != index1 && numbers[i] > numbers[index2])
      index2 = i;

  return numbers[index1] * numbers[index2];
}
