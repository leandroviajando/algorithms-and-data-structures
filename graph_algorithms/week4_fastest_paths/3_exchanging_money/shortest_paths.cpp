#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using std::pair;
using std::priority_queue;
using std::queue;
using std::vector;

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
}

int main() {
  int n, m, s;
  std::cin >> n >> m;

  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }

  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);

  for (int i = 0; i < n; i++) {
    if (!reachable[i])
      std::cout << "*";
    else if (!shortest[i])
      std::cout << "-";
    else
      std::cout << distance[i];
    std::cout << std::endl;
  }
}
