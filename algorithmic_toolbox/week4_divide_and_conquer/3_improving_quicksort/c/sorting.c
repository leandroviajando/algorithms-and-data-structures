#include <stdio.h>
#include <stdlib.h>

struct Pair {
  int first;
  int second;
};

struct Pair partition3(int *a, int l, int r) {
  int x = a[l];
  int j = l;
  int m = l;
  int n = r;
  int i = l + 1;
  while (i <= n) {
    if (a[i] < x) {
      j++;
      int temp1 = a[i];
      a[i] = a[j];
      a[j] = temp1;
      m++;
      int temp2 = a[j];
      a[j] = a[m];
      a[m] = temp2;
      i++;
    } else if (a[i] == x) {
      j++;
      int temp3 = a[i];
      a[i] = a[j];
      a[j] = temp3;
      i++;
    } else {
      int temp4 = a[i];
      a[i] = a[n];
      a[n] = temp4;
      n--;
    }
  }
  int temp5 = a[l];
  a[l] = a[m];
  a[m] = temp5;
  struct Pair result;
  result.first = m;
  result.second = j;
  return result;
}

int partition2(int *a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      int temp = a[i];
      a[i] = a[j];
      a[j] = temp;
    }
  }
  int temp2 = a[l];
  a[l] = a[j];
  a[j] = temp2;
  return j;
}

void randomized_quick_sort(int *a, int l, int r, int use_partition3) {
  if (l >= r) return;

  int k = l + rand() % (r - l + 1);
  int temp = a[l];
  a[l] = a[k];
  a[k] = temp;

  if (use_partition3) {
    struct Pair result = partition3(a, l, r);
    randomized_quick_sort(a, l, result.first - 1, 1);
    randomized_quick_sort(a, result.second + 1, r, 1);
  } else {
    int m = partition2(a, l, r);
    randomized_quick_sort(a, l, m - 1, 0);
    randomized_quick_sort(a, m + 1, r, 0);
  }
}
