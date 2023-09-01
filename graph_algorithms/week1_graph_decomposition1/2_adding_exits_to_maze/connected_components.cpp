#include <iostream>
#include <vector>

using std::pair;
using std::vector;

// Marks all vertices reachable from u as visited.
void explore(vector<vector<int>> &adj, vector<bool> &visited, int u) {
  visited[u] = true;

  for (int v : adj[u])
    if (!visited[v])
      explore(adj, visited, v);
}

// Returns the number of connected components in the given undirected graph.
int number_of_components(vector<vector<int>> &adj) {
  int res = 0;

  vector<bool> visited = vector<bool>(adj.size(), false);
  for (int u = 0; u < adj.size(); u++)
    if (!visited[u]) {
      explore(adj, visited, u);
      res++;
    }

  return res;
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

  std::cout << number_of_components(adj) << std::endl;
}
