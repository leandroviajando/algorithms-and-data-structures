#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
  return a < b ? a : b;
}

/* Levenshtein distance: insertion, deletion, substitution */
int edit_distance(const char* s, const char* t) {
  if (strcmp(s, t) == 0) return 0;

  int m = strlen(s), n = strlen(t);
  int dp[m + 1][n + 1];

  for (int i = 0; i <= m; ++i) dp[i][0] = i;

  for (int j = 0; j <= n; ++j) dp[0][j] = j;

  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= n; ++j)
      if (s[i - 1] == t[j - 1])
        dp[i][j] = dp[i - 1][j - 1];
      else
        dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;

  return dp[m][n];
}

int main() {
  char s[1001], t[1001];
  int _ = scanf("%s %s", s, t);
  printf("%d\n", edit_distance(s, t));
  return 0;
}
