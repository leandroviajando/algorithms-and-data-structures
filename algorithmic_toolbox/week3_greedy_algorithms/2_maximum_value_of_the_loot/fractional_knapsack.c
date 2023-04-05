#include <stdio.h>
#include <stdlib.h>

struct Item {
  int weight;
  int value;
  double unit_value;
};

int compare(const void* a, const void* b) {
  const struct Item* item_a = (const struct Item*)a;
  const struct Item* item_b = (const struct Item*)b;
  return (item_b->unit_value > item_a->unit_value) - (item_a->unit_value > item_b->unit_value);
}

double get_optimal_value(int capacity, int* weights, int* values, int n) {
  int weight = 0;
  double value = 0.0;

  struct Item* items = (struct Item*)malloc(n * sizeof(struct Item));
  for (int i = 0; i < n; i++) {
    items[i].weight = weights[i];
    items[i].value = values[i];
    items[i].unit_value = (double)values[i] / weights[i];
  }

  qsort(items, n, sizeof(struct Item), compare);

  for (int i = 0; i < n; i++) {
    if (weight >= capacity) break;

    int units = (items[i].weight < capacity - weight) ? items[i].weight : (capacity - weight);
    weight += units;
    value += units * items[i].unit_value;
  }

  free(items);
  return value;
}

int main() {
  int n;
  int capacity;
  int _ = scanf("%d %d", &n, &capacity);
  int* values = (int*)malloc(n * sizeof(int));
  int* weights = (int*)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    int _ = scanf("%d %d", &values[i], &weights[i]);
  }

  double optimal_value = get_optimal_value(capacity, weights, values, n);

  printf("%.10lf\n", optimal_value);
  free(values);
  free(weights);
  return 0;
}
