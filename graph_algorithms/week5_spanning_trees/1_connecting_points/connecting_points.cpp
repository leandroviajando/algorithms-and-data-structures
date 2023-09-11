#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using std::vector;

struct Edge {
  int u, v;
  double weight;
};

bool compareEdges(const Edge& a, const Edge& b) {
  return a.weight < b.weight;
}

// Function to find the parent of a vertex in the disjoint-set (union-find) data structure.
int findParent(vector<int>& parent, int vertex) {
  if (parent[vertex] == -1)
    return vertex;
  return findParent(parent, parent[vertex]);
}

// Function to perform union of two sets in the disjoint-set (union-find) data structure.
void unionSets(vector<int>& parent, int u, int v) {
  int uParent = findParent(parent, u);
  int vParent = findParent(parent, v);
  if (uParent != vParent)
    parent[uParent] = vParent;
}

double minimum_distance(vector<int> x, vector<int> y) {
  size_t n = x.size();
  vector<Edge> edges;

  // Create edges from all pairs of points with their Euclidean distances as weights.
  for (size_t i = 0; i < n; i++) {
    for (size_t j = i + 1; j < n; j++) {
      double dist = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      edges.push_back({static_cast<int>(i), static_cast<int>(j), dist});
    }
  }

  // Sort edges by weight in ascending order.
  std::sort(edges.begin(), edges.end(), compareEdges);

  // Initialize a disjoint-set (union-find) data structure.
  vector<int> parent(n, -1);

  double result = 0.0;
  for (const Edge& edge : edges) {
    int u = edge.u;
    int v = edge.v;
    double weight = edge.weight;

    // Check if adding this edge does not create a cycle in the current spanning tree.
    if (findParent(parent, u) != findParent(parent, v)) {
      result += weight;
      unionSets(parent, u, v);
    }
  }

  return result;
}

int main() {
  size_t n;
  std::cin >> n;

  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++)
    std::cin >> x[i] >> y[i];

  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
