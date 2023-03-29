#include <stdio.h>
#include <stdlib.h>

long long merge(int a[], int b[], size_t left, size_t ave, size_t right) {
  size_t i = left;
  size_t j = ave + 1;
  size_t k = left;
  long long inv_count = 0;

  while (i <= ave && j <= right) {
    if (a[i] <= a[j]) {
      b[k] = a[i];
      k += 1;
      i += 1;
    } else {
      inv_count += ave - i + 1;
      b[k] = a[j];
      k += 1;
      j += 1;
    }
  }

  while (i <= ave) {
    b[k] = a[i];
    k += 1;
    i += 1;
  }

  while (j <= right) {
    b[k] = a[j];
    k += 1;
    j += 1;
  }

  for (i = left; i <= right; i++)
    a[i] = b[i];

  return inv_count;
}

long long getNumberOfInversions(int a[], int b[], size_t left, size_t right) {
  long long number_of_inversions = 0;

  if (right <= left + 1)
    return number_of_inversions;

  size_t ave = (left + right) / 2;
  number_of_inversions += getNumberOfInversions(a, b, left, ave);
  number_of_inversions += getNumberOfInversions(a, b, ave, right);
  number_of_inversions += merge(a, b, left, ave - 1, right - 1);

  return number_of_inversions;
}
