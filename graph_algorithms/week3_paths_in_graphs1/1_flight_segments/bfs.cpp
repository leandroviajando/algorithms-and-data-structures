#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

int distance(vector<vector<int> > &adj, int s, int t) {
  vector<int> dist(adj.size(), -1);
  dist[s] = 0;
  queue<int> q;
  q.push(s);
  while (dist[t] == -1 && !q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : adj[u])
      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
  }
  return dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;

  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  int u, v;
  std::cin >> u >> v;
  std::cout << distance(adj, u - 1, v - 1) << std::endl;
}
