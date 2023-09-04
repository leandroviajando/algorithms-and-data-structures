#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

int bipartite(vector<vector<int> > &adj) {
  vector<int> colour(adj.size(), -1);
  colour[0] = 0;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : adj[u]) {
      if (colour[v] == -1) {
        colour[v] = 1 - colour[u];
        q.push(v);
      } else if (colour[v] == colour[u])
        return 0;
    }
  }
  return 1;
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

  std::cout << bipartite(adj) << std::endl;
}
