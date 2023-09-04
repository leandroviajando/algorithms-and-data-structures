#include <iostream>
#include <queue>
#include <vector>

using std::pair;
using std::priority_queue;
using std::queue;
using std::vector;

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  vector<long long> dist(adj.size(), __LONG_LONG_MAX__);
  vector<int> prev(adj.size(), -1);
  vector<bool> visited(adj.size(), false);
  dist[s] = 0;
  priority_queue<pair<long long, int> > pq;
  pq.push(std::make_pair(0, s));
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();

    if (!visited[u]) {
      visited[u] = true;
      for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (dist[v] > dist[u] + cost[u][i]) {
          dist[v] = dist[u] + cost[u][i];
          prev[v] = u;
          pq.push(std::make_pair(-dist[v], v));
        }
      }
    }
  }
  return dist[t] == __LONG_LONG_MAX__ ? -1 : dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;

  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }

  int u, v;
  std::cin >> u >> v;
  std::cout << distance(adj, cost, u - 1, v - 1) << std::endl;
}
