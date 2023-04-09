#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

/* Longest common subsequence: insertion, deletion; no substitution */
int lcs2(const std::vector<int>& a, const std::vector<int>& b) {
  std::set<int> s(a.begin(), a.end());
  std::set<int> t(b.begin(), b.end());

  if (std::find_first_of(s.begin(), s.end(), std::begin(t), std::end(t)) == s.end())
    return 0;

  int m = a.size(), n = b.size();
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= n; ++j)
      if (a[i - 1] == b[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);

  return dp[m][n];
}

int main() {
  size_t n;
  std::cin >> n;
  std::vector<int> a(n);
  for (size_t i = 0; i < n; i++)
    std::cin >> a[i];

  size_t m;
  std::cin >> m;
  std::vector<int> b(m);
  for (size_t i = 0; i < m; i++)
    std::cin >> b[i];

  std::cout << lcs2(a, b) << std::endl;
}
