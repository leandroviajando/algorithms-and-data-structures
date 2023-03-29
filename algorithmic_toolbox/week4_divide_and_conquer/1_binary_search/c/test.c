#include <assert.h>
#include <stdio.h>

#include "binary_search.h"

void test_binary_search() {
  int numbers1[] = {1, 5, 8, 12, 13};
  assert(binary_search(numbers1, 5, 8) == 2);
  assert(binary_search(numbers1, 5, 1) == 0);
  assert(binary_search(numbers1, 5, 23) == -1);
  assert(binary_search(numbers1, 5, 1) == 0);
  assert(binary_search(numbers1, 5, 11) == -1);

  int numbers2[] = {1, 2, 3, 4, 5};
  assert(binary_search(numbers2, 5, 1) == 0);
  assert(binary_search(numbers2, 5, 2) == 1);
  assert(binary_search(numbers2, 5, 3) == 2);
  assert(binary_search(numbers2, 5, 4) == 3);
  assert(binary_search(numbers2, 5, 5) == 4);
}

int main() {
  test_binary_search();
  printf("All tests passed successfully.\n");
  return 0;
}
