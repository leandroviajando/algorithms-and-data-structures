#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

/* Longest common subsequence: insertion, deletion; no substitution */
int lcs3(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& c) {
  int m = a.size(), n = b.size(), o = c.size();
  std::vector<std::vector<std::vector<int>>> dp(m + 1, std::vector<std::vector<int>>(n + 1, std::vector<int>(o + 1, 0)));

  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= n; ++j)
      for (int k = 1; k <= o; ++k)
        if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1])
          dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
        else
          dp[i][j][k] = std::max({dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]});

  return dp[m][n][o];
}

int main() {
  size_t an;
  std::cin >> an;
  std::vector<int> a(an);
  for (size_t i = 0; i < an; i++) std::cin >> a[i];

  size_t bn;
  std::cin >> bn;
  std::vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) std::cin >> b[i];

  size_t cn;
  std::cin >> cn;
  std::vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) std::cin >> c[i];

  std::cout << lcs3(a, b, c) << std::endl;
}
