#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "sorting.h"

void test_randomized_quick_sort() {
  int a[] = {2, 3, 9, 2, 2};
  int n = sizeof(a) / sizeof(a[0]);
  randomized_quick_sort(a, 0, n - 1, 0);
  for (int i = 1; i < n; i++)
    assert(a[i - 1] <= a[i]);
}

int main() {
  test_randomized_quick_sort();
  printf("All tests passed successfully.\n");
  return 0;
}
