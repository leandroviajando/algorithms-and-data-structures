#include <iostream>
#include <vector>

using std::pair;
using std::vector;

bool isCyclicDFS(vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &visitedDuringCurrentTraversal, int v) {
  visited[v] = true;
  visitedDuringCurrentTraversal[v] = true;

  for (int w : adj[v])
    if (visitedDuringCurrentTraversal[w] || isCyclicDFS(adj, visited, visitedDuringCurrentTraversal, w))
      return true;

  visitedDuringCurrentTraversal[v] = false;  // Reset before next traversal
  return false;
}

// Returns 0 if the directed graph is acyclic, 1 otherwise.
int acyclic(vector<vector<int>> &adj) {
  int n = adj.size();
  vector<bool> visited(n, false);
  vector<bool> visitedDuringCurrentTraversal(n, false);

  for (int v = 0; v < n; v++)
    if (!visited[v] && isCyclicDFS(adj, visited, visitedDuringCurrentTraversal, v))
      return 1;

  return 0;
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

  std::cout << acyclic(adj) << std::endl;
}
