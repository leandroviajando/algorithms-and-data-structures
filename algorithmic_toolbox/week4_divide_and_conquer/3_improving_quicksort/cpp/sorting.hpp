#ifndef MAX_PAIRWISE_PRODUCT_H
#define MAX_PAIRWISE_PRODUCT_H

#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

using std::pair;
using std::swap;
using std::vector;

pair<int, int> partition3(vector<int> &a, int l, int r);
int partition2(vector<int> &a, int l, int r);
void randomized_quick_sort(vector<int> &a, int l, int r, bool use_partition3 = true);

#endif /* MAX_PAIRWISE_PRODUCT_H */
