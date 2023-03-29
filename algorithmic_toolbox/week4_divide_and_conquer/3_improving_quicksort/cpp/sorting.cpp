#include <cstdlib>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using std::pair;
using std::swap;
using std::vector;

pair<int, int> partition3(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  int m = l;
  int n = r;
  int i = l + 1;
  while (i <= n) {
    if (a[i] < x) {
      j++;
      swap(a[i], a[j]);
      m++;
      swap(a[j], a[m]);
      i++;
    } else if (a[i] == x) {
      j++;
      swap(a[i], a[j]);
      i++;
    } else {
      swap(a[i], a[n]);
      n--;
    }
  }
  swap(a[l], a[m]);
  return {m, j};
}

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r, bool use_partition3 = true) {
  if (l >= r) return;

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);

  if (use_partition3) {
    int m, j;
    std::tie(m, j) = partition3(a, l, r);
    randomized_quick_sort(a, l, m - 1);
    randomized_quick_sort(a, j + 1, r);
  } else {
    int m = partition2(a, l, r);
    randomized_quick_sort(a, l, m - 1, false);
    randomized_quick_sort(a, m + 1, r, false);
  }
}
