#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *data;
  size_t size;
} vector;

void vector_init(vector *v) {
  v->data = NULL;
  v->size = 0;
}

void vector_push_back(vector *v, int value) {
  v->data = realloc(v->data, sizeof(int) * (v->size + 1));
  v->data[v->size] = value;
  ++v->size;
}

vector optimal_summands(int n) {
  vector summands;
  vector_init(&summands);

  for (int i = 1; i <= n; i++) {
    if (n - i > i) {
      vector_push_back(&summands, i);
      n -= i;
    } else {
      vector_push_back(&summands, n);
      break;
    }
  }

  return summands;
}

int main() {
  int n;
  int _ = scanf("%d", &n);

  vector summands = optimal_summands(n);

  printf("%lu\n", summands.size);
  for (size_t i = 0; i < summands.size; ++i)
    printf("%d ", summands.data[i]);

  free(summands.data);
  return 0;
}
