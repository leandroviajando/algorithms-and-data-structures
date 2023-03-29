#ifndef SORTING_H
#define SORTING_H

struct Pair partition3(int *a, int l, int r);
int partition2(int *a, int l, int r);
void randomized_quick_sort(int *a, int l, int r, int use_partition3);

#endif /* SORTING_H */
