#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "inversions.h"

void test_getNumberOfInversions() {
  int a[] = {2, 3, 9, 2, 9};
  int n = sizeof(a) / sizeof(int);
  int b[n];
  int inv_count = getNumberOfInversions(a, b, 0, n);
  assert(inv_count == 2);
}

int main() {
  test_getNumberOfInversions();
  printf("All tests passed successfully.\n");
  return 0;
}
