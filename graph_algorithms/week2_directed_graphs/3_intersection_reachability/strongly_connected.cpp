#include <iostream>
#include <stack>
#include <vector>

using std::vector;

void explore(vector<vector<int>>& adj, vector<bool>& visited, int u) {
  visited[u] = true;

  for (int v : adj[u])
    if (!visited[v])
      explore(adj, visited, v);
}

void topologicalSort(vector<vector<int>>& adj, vector<bool>& visited, std::stack<int>& s, int u) {
  visited[u] = true;

  for (int v : adj[u])
    if (!visited[v])
      topologicalSort(adj, visited, s, v);

  s.push(u);
}

int number_of_strongly_connected_components(vector<vector<int>>& adj) {
  int res = 0;

  int n = adj.size();
  vector<bool> visited(n, false);
  std::stack<int> s;

  for (int u = 0; u < n; u++)
    if (!visited[u])
      topologicalSort(adj, visited, s, u);

  vector<vector<int>> reverse_adj(n, vector<int>());
  for (int u = 0; u < n; u++)
    for (int v : adj[u])
      reverse_adj[v].push_back(u);

  visited.assign(n, false);

  while (!s.empty()) {
    int u = s.top();
    s.pop();

    if (!visited[u]) {
      explore(reverse_adj, visited, u);
      res++;
    }
  }

  return res;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int a, b;
    std::cin >> a >> b;
    adj[a - 1].push_back(b - 1);
  }

  std::cout << number_of_strongly_connected_components(adj) << std::endl;
  return 0;
}
