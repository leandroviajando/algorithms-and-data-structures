#include <algorithm>
#include <climits>
#include <deque>
#include <iostream>
#include <vector>

using std::deque;
using std::vector;

namespace stock_charts {
vector<vector<int>> dag(int n, const vector<vector<int>>& stock) {
  vector<vector<int>> graph(n, vector<int>(n, 0));

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      bool above = true;
      bool below = true;

      for (int k = 0; k < stock[i].size(); ++k) {
        if (stock[i][k] >= stock[j][k])
          above = false;
        if (stock[i][k] <= stock[j][k])
          below = false;
      }

      if (above)
        graph[i][j] = 1;
      else if (below)
        graph[j][i] = 1;
    }
  }

  return graph;
}

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

int max_flow(vector<vector<int>>& graph, int n) {
  int V = graph.size();
  vector<int> path(V, -1);
  int flow = 0;

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

    flow += min_flow;
  }

  return flow;
}
}  // namespace stock_charts

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int>> stock_data(n, vector<int>());
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; j++) {
      int bit;
      std::cin >> bit;
      stock_data[i].push_back(bit);
    }
  }

  vector<vector<int>> adj_matrix = stock_charts::dag(n, stock_data);
  vector<vector<int>> residual_graph = stock_charts::build_network(n, n, adj_matrix);
  int min_charts = n - stock_charts::max_flow(residual_graph, n);

  std::cout << min_charts << std::endl;
  return 0;
}
