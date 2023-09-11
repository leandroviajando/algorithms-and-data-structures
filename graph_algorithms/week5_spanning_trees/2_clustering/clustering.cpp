#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

using std::pair;
using std::tuple;
using std::vector;

int find(vector<int>& parent, int i) {
  if (i != parent[i]) {
    parent[i] = find(parent, parent[i]);
  }
  return parent[i];
}

void unionSets(vector<int>& parent, vector<int>& rank, int i, int j) {
  int iParent = find(parent, i);
  int jParent = find(parent, j);
  if (iParent == jParent)
    return;

  if (rank[iParent] > rank[jParent])
    parent[jParent] = iParent;
  else {
    parent[iParent] = jParent;
    if (rank[iParent] == rank[jParent])
      rank[jParent]++;
  }
}

float min_distance_clustering(vector<tuple<int, int, float>>& edges, int n, int k) {
  vector<int> parent(n);
  vector<int> rank(n, 0);
  int nEdge = 0;

  for (int i = 0; i < n; i++)
    parent[i] = i;

  sort(edges.begin(), edges.end(), [](const tuple<int, int, float>& a, const tuple<int, int, float>& b) {
    return std::get<2>(a) < std::get<2>(b);
  });

  for (const auto& edge : edges) {
    int u, v;
    float w;
    std::tie(u, v, w) = edge;
    if (find(parent, u) != find(parent, v)) {
      if (nEdge == n - k)
        return w;

      nEdge++;
      unionSets(parent, rank, u, v);
    }
  }

  return 0.0;
}

int main() {
  int nVertices;
  std::cin >> nVertices;
  vector<pair<int, int>> points(nVertices);

  for (int i = 0; i < nVertices; i++) {
    int a, b;
    std::cin >> a >> b;
    points[i] = std::make_pair(a, b);
  }

  int nSubsets;
  std::cin >> nSubsets;

  vector<tuple<int, int, float>> edges;

  for (int i = 0; i < nVertices; i++) {
    int x0, y0;
    std::tie(x0, y0) = points[i];
    for (int j = i + 1; j < nVertices; j++) {
      int x, y;
      std::tie(x, y) = points[j];
      float distance = sqrt(pow(x - x0, 2) + pow(y - y0, 2));
      edges.push_back(std::make_tuple(i, j, distance));
    }
  }

  std::cout << std::fixed << std::setprecision(9) << min_distance_clustering(edges, nVertices, nSubsets) << std::endl;

  return 0;
}
