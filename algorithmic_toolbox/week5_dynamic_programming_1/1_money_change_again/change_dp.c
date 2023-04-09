#include <stdio.h>
#include <stdlib.h>

const int COINS[] = {1, 3, 4};
const int NUM_COINS = sizeof(COINS) / sizeof(int);

int get_change(int m) {
  int dp[m + 1];

  dp[0] = 0;
  for (int i = 1; i <= m; i++) dp[i] = m + 1;

  for (int i = 1; i <= m; i++) {
    for (int j = 0; j < NUM_COINS; j++) {
      int coin = COINS[j];
      if (i >= coin && dp[i - coin] + 1 < dp[i])
        dp[i] = dp[i - coin] + 1;
    }
  }

  if (dp[m] > m) {
    printf("Something went wrong\n");
    exit(EXIT_FAILURE);
  }

  return dp[m];
}

int main() {
  int m;
  int _ = scanf("%d", &m);
  printf("%d\n", get_change(m));

  return 0;
}
