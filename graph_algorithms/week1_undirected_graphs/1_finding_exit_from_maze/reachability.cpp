#include <iostream>
#include <vector>

using std::vector;

// Returns 1 if there is a path between u and v, 0 otherwise.
int dfs(vector<vector<int>> &adj, vector<bool> &visited, int u, int v) {
  if (u == v)
    return 1;

  visited[u] = true;

  for (int i = 0; i < adj[u].size(); i++) {
    int w = adj[u][i];

    if (!visited[w] && dfs(adj, visited, w, v))
      return 1;
  }

  return 0;
}

// Returns 1 if there is a path between u and v, 0 otherwise.
int reach(vector<vector<int>> &adj, int u, int v) {
  vector<bool> visited(adj.size(), false);
  return dfs(adj, visited, u, v);
}

int main() {
  size_t n, m;
  std::cin >> n >> m;

  vector<vector<int>> adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int a, b;
    std::cin >> a >> b;
    adj[a - 1].push_back(b - 1);
    adj[b - 1].push_back(a - 1);
  }

  int u, v;
  std::cin >> u >> v;
  std::cout << reach(adj, u - 1, v - 1) << std::endl;
}
