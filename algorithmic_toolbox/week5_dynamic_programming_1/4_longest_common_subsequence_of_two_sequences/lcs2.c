#include <stdio.h>
#include <stdlib.h>

int find_first_of(int* begin1, int* end1, int* begin2, int* end2) {
  while (begin1 != end1) {
    for (int* it = begin2; it != end2; it++)
      if (*it == *begin1) return 1;
    begin1++;
  }
  return 0;
}

/* Longest common subsequence: insertion, deletion; no substitution */
int lcs2(const int* a, const int a_size, const int* b, const int b_size) {
  int s[a_size];
  int t[b_size];
  for (int i = 0; i < a_size; i++) s[i] = a[i];
  for (int i = 0; i < b_size; i++) t[i] = b[i];

  int s_size = a_size;
  int t_size = b_size;

  int found = find_first_of(s, s + s_size, t, t + t_size);
  if (!found) return 0;

  int dp[a_size + 1][b_size + 1];

  for (int i = 0; i <= a_size; ++i)
    for (int j = 0; j <= b_size; ++j)
      dp[i][j] = 0;

  for (int i = 1; i <= a_size; ++i)
    for (int j = 1; j <= b_size; ++j)
      if (s[i - 1] == t[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];

  return dp[a_size][b_size];
}

int main() {
  int n;
  scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);

  int m;
  scanf("%d", &m);
  int b[m];
  for (int i = 0; i < m; i++) scanf("%d", &b[i]);

  printf("%d\n", lcs2(a, n, b, m));

  return 0;
}
