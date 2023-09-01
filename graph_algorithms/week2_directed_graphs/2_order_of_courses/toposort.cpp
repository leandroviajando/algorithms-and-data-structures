#include <algorithm>
#include <iostream>
#include <vector>

using std::pair;
using std::vector;

void dfs(vector<vector<int>> &adj, vector<bool> &used, vector<int> &order, int v) {
  used[v] = true;

  for (int w : adj[v])
    if (!used[w])
      dfs(adj, used, order, w);

  order.push_back(v);
}

vector<int> toposort(vector<vector<int>> &adj) {
  vector<bool> used = vector<bool>(adj.size(), false);
  vector<int> order;

  for (int v = 0; v < adj.size(); v++)
    if (!used[v])
      dfs(adj, used, order, v);

  std::reverse(order.begin(), order.end());

  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;

  vector<vector<int>> adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int a, b;
    std::cin >> a >> b;
    adj[a - 1].push_back(b - 1);
  }

  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++)
    std::cout << order[i] + 1 << " ";
  std::cout << std::endl;
}
