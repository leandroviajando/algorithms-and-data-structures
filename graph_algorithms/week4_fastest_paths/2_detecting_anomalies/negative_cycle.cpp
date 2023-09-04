#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int>> &adj, vector<vector<int>> &cost) {
  int n = adj.size();
  vector<long long> dist(n, 0);

  // Perform n iterations of relaxation.
  for (int k = 0; k < n; k++) {
    for (int u = 0; u < n; u++) {
      for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];

        if (dist[v] > dist[u] + cost[u][i])
          dist[v] = dist[u] + cost[u][i];
      }
    }
  }

  // Check for negative cycles.
  for (int u = 0; u < n; u++) {
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];

      if (dist[v] > dist[u] + cost[u][i])
        return 1;
    }
  }

  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  vector<vector<int>> adj(n, vector<int>());
  vector<vector<int>> cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }

  std::cout << negative_cycle(adj, cost) << std::endl;
}
