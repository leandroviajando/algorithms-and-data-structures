#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

int compare(const void *a, const void *b) {
  char ab[MAX_LENGTH * 2 + 1], ba[MAX_LENGTH * 2 + 1];
  strcpy(ab, *(const char **)a);
  strcat(ab, *(const char **)b);
  strcpy(ba, *(const char **)b);
  strcat(ba, *(const char **)a);
  return strcmp(ba, ab);
}

char *largest_number(char **a, int n) {
  qsort(a, n, sizeof(char *), compare);
  char *result = (char *)malloc((MAX_LENGTH * n + 1) * sizeof(char));
  result[0] = '\0';
  for (int i = 0; i < n; i++) {
    strcat(result, a[i]);
  }
  return result;
}

int main() {
  int n;
  int _ = scanf("%d", &n);
  char **a = (char **)malloc(n * sizeof(char *));
  for (int i = 0; i < n; i++) {
    a[i] = (char *)malloc((MAX_LENGTH + 1) * sizeof(char));
    int _ = scanf("%s", a[i]);
  }
  char *result = largest_number(a, n);
  printf("%s", result);
  free(result);
  for (int i = 0; i < n; i++) {
    free(a[i]);
  }
  free(a);
  return 0;
}
