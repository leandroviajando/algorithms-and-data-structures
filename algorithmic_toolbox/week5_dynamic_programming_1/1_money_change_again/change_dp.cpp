#include <algorithm>
#include <iostream>
#include <vector>

const std::vector<int> COINS = {1, 3, 4};

int get_change(int m) {
  std::vector<int> dp(m + 1, m + 1);

  for (int i = 1; i <= m; i++) {
    if (find(COINS.begin(), COINS.end(), i) != COINS.end())
      dp[i] = 1;
    else
      for (const auto& coin : COINS)
        if (i >= coin)
          dp[i] = std::min(dp[i], dp[i - coin] + 1);
  }

  if (dp[m] > m)
    throw std::runtime_error("Something went wrong");

  return dp[m];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << std::endl;

  return 0;
}
