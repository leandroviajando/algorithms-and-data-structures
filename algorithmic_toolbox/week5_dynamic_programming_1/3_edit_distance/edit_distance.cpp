#include <iostream>
#include <vector>

/* Levenshtein distance: insertion, deletion, substitution */
int edit_distance(const std::string& s, const std::string& t) {
  if (s == t) return 0;

  int m = s.length(), n = t.length();
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

  for (int i = 0; i <= m; ++i) dp[i][0] = i;

  for (int j = 0; j <= n; ++j) dp[0][j] = j;

  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= n; ++j)
      if (s[i - 1] == t[j - 1])
        dp[i][j] = dp[i - 1][j - 1];
      else
        dp[i][j] = std::min(dp[i - 1][j], std::min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;

  return dp[m][n];
}

int main() {
  std::string s, t;
  std::cin >> s >> t;
  std::cout << edit_distance(s, t) << std::endl;
  return 0;
}
