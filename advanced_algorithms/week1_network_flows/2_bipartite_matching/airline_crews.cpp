#include <algorithm>
#include <climits>
#include <deque>
#include <iostream>
#include <vector>

using std::deque;
using std::vector;

namespace airline_crews {
vector<vector<int>> build_network(int n, int m, const vector<vector<int>>& adj) {
  vector<vector<int>> graph(n + m + 2, vector<int>(n + m + 2, 0));

  for (int i = 1; i <= n; ++i) {
    graph[0][i] = 1;

    for (int j = 0; j < m; ++j)
      graph[i][n + 1 + j] = adj[i - 1][j];
  }

  for (int k = n + 1; k <= n + m; ++k)
    graph[k][n + m + 1] = 1;

  return graph;
}

bool hasPath(const vector<vector<int>>& graph, vector<int>& path) {
  int V = graph.size();
  vector<bool> visited(V, false);
  visited[0] = true;
  deque<int> q;
  q.push_back(0);

  while (!q.empty()) {
    int u = q.front();
    q.pop_front();

    if (u == V - 1)
      return true;

    for (int v = 0; v < V; ++v) {
      if (!visited[v] && graph[u][v] > 0) {
        visited[v] = true;
        q.push_back(v);
        path[v] = u;
      }
    }
  }

  return visited[V - 1];
}

int findIndex(vector<int>& matrix, int target) {
  for (int i = 0; i < matrix.size(); i++)
    if (matrix[i] == target)
      return i;
  return -1;
}

vector<int> max_flow(vector<vector<int>>& graph, int n) {
  int V = graph.size();
  vector<int> path(V);
  for (int i = 0; i < V; ++i)
    path[i] = i;

  while (hasPath(graph, path)) {
    int min_flow = INT_MAX;
    int v = V - 1;

    while (v > 0) {
      int u = path[v];
      min_flow = std::min(min_flow, graph[u][v]);
      v = u;
    }

    v = V - 1;
    while (v > 0) {
      int u = path[v];
      graph[u][v] -= min_flow;
      graph[v][u] += min_flow;
      v = u;
    }
  }

  vector<int> matching(n, -1);
  for (int i = 0; i < V; ++i) {
    if (graph[V - 1][i] == 1) {
      int person = i - n - 1;
      int flight = findIndex(graph[i], 1);
      matching[flight - 1] = person;
    }
  }

  return matching;
}
}  // namespace airline_crews

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int>> bipartite_graph(n, vector<int>());
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; j++) {
      int bit;
      std::cin >> bit;
      bipartite_graph[i].push_back(bit);
    }
  }

  vector<vector<int>> residual_graph = airline_crews::build_network(n, m, bipartite_graph);
  vector<int> matching = airline_crews::max_flow(residual_graph, n);

  for (int i = 0; i < matching.size(); ++i) {
    if (i > 0)
      std::cout << " ";

    if (matching[i] == -1)
      std::cout << "-1";
    else
      std::cout << (matching[i] + 1);
  }
  std::cout << std::endl;
}
