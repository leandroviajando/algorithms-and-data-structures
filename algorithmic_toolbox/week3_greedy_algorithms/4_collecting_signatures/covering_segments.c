#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int start, end;
} Segment;

int compare_segment(const void* a, const void* b) {
  Segment* s1 = (Segment*)a;
  Segment* s2 = (Segment*)b;

  return s1->end - s2->end;
}

int* optimal_points(Segment* segments, int n, int* len) {
  qsort(segments, n, sizeof(Segment), compare_segment);

  int* points = malloc(sizeof(int) * n);
  int point_count = 0;

  while (n > 0) {
    int point = segments[0].end;
    points[point_count++] = point;

    for (int i = 0; i < n; ++i) {
      if (segments[i].start <= point && point <= segments[i].end) {
        segments[i] = segments[--n];
        i--;
      }
    }

    segments = realloc(segments, sizeof(Segment) * n);
  }

  *len = point_count;
  return points;
}

int main() {
  int n;
  int _ = scanf("%d", &n);

  Segment* segments = malloc(sizeof(Segment) * n);
  for (int i = 0; i < n; i++) {
    int _ = scanf("%d %d", &segments[i].start, &segments[i].end);
  }

  int point_count;
  int* points = optimal_points(segments, n, &point_count);
  printf("%d\n", point_count);

  for (int i = 0; i < point_count; i++) {
    printf("%d ", points[i]);
  }
  printf("\n");

  free(segments);
  free(points);

  return 0;
}
