#include <stdio.h>
#include <stdlib.h>

/* Longest common subsequence: insertion, deletion; no substitution */
int lcs3(const int *a, int a_size, const int *b, int b_size, const int *c, int c_size) {
  int m = a_size, n = b_size, o = c_size;
  int ***dp = (int ***)malloc((m + 1) * sizeof(int **));
  for (int i = 0; i <= m; i++) {
    dp[i] = (int **)malloc((n + 1) * sizeof(int *));
    for (int j = 0; j <= n; j++) dp[i][j] = (int *)calloc((o + 1), sizeof(int));
  }

  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= n; ++j)
      for (int k = 1; k <= o; ++k) {
        if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1])
          dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
        else
          dp[i][j][k] = ((dp[i - 1][j][k] > dp[i][j - 1][k]) ? dp[i - 1][j][k] : dp[i][j - 1][k]);
        dp[i][j][k] = ((dp[i][j][k - 1] > dp[i][j][k]) ? dp[i][j][k - 1] : dp[i][j][k]);
      }

  int res = dp[m][n][o];
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) free(dp[i][j]);
    free(dp[i]);
  }
  free(dp);
  return res;
}

int main() {
  size_t an;
  scanf("%zu", &an);
  int *a = (int *)malloc(an * sizeof(int));
  for (size_t i = 0; i < an; i++) scanf("%d", &a[i]);

  size_t bn;
  scanf("%zu", &bn);
  int *b = (int *)malloc(bn * sizeof(int));
  for (size_t i = 0; i < bn; i++) scanf("%d", &b[i]);

  size_t cn;
  scanf("%zu", &cn);
  int *c = (int *)malloc(cn * sizeof(int));
  for (size_t i = 0; i < cn; i++) scanf("%d", &c[i]);

  printf("%d\n", lcs3(a, an, b, bn, c, cn));
  free(a);
  free(b);
  free(c);
}
