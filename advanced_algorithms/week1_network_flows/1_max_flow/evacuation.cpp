#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
 public:
  struct Edge {
    int from, to, capacity, flow;
  };

 private:
  /* List of all - forward and backward - edges */
  vector<Edge> edges;

  /* These adjacency lists store only indices of edges in the edges list */
  vector<vector<size_t> > graph;

 public:
  explicit FlowGraph(size_t n) : graph(n) {}

  void add_edge(int from, int to, int capacity) {
    /* Note that we first append a forward edge and then a backward edge,
     * so all forward edges are stored at even indices (starting from 0),
     * whereas backward edges are stored at odd indices in the list edges */
    Edge forward_edge = {from, to, capacity, 0};
    Edge backward_edge = {to, from, 0, 0};
    graph[from].push_back(edges.size());
    edges.push_back(forward_edge);
    graph[to].push_back(edges.size());
    edges.push_back(backward_edge);
  }

  size_t size() const {
    return graph.size();
  }

  const vector<size_t>& get_ids(int from) const {
    return graph[from];
  }

  const Edge& get_edge(size_t id) const {
    return edges[id];
  }

  void add_flow(size_t id, int flow) {
    /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
     * due to the described above scheme. On the other hand, when we have to get a "backward"
     * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
     * should be taken.
     *
     * It turns out that id ^ 1 works for both cases. Think this through! */
    edges[id].flow += flow;
    edges[id ^ 1].flow -= flow;
  }
};

FlowGraph read_data() {
  int vertex_count, edge_count;
  std::cin >> vertex_count >> edge_count;
  FlowGraph graph(vertex_count);
  for (int i = 0; i < edge_count; ++i) {
    int u, v, capacity;
    std::cin >> u >> v >> capacity;
    graph.add_edge(u - 1, v - 1, capacity);
  }
  return graph;
}

/* Ford-Fulkerson algorithm with the Edmonds-Karp variant,
which uses BFS to find augmenting paths */
int max_flow(FlowGraph& graph, int from, int to) {
  int flow = 0;

  // Continue until no augmenting path is found
  while (true) {
    // Use Breadth-First Search (BFS) to find an augmenting path
    vector<int> parent(graph.size(), -1);
    queue<int> q;
    q.push(from);

    while (!q.empty() && parent[to] == -1) {
      int current = q.front();
      q.pop();

      for (size_t i : graph.get_ids(current)) {
        const FlowGraph::Edge& edge = graph.get_edge(i);

        // Check if the edge can carry more flow and if we haven't visited the neighbor yet
        if (parent[edge.to] == -1 && edge.capacity > edge.flow) {
          q.push(edge.to);
          parent[edge.to] = i;  // Store the edge ID to backtrack
        }
      }
    }

    // If no augmenting path is found, we're done
    if (parent[to] == -1)
      break;

    // Find the maximum possible flow in the augmenting path
    int min_capacity = __INT_MAX__;
    for (int v = to; v != from; v = graph.get_edge(parent[v]).from) {
      const FlowGraph::Edge& edge = graph.get_edge(parent[v]);
      min_capacity = std::min(min_capacity, edge.capacity - edge.flow);
    }

    // Update the flow along the augmenting path
    for (int v = to; v != from; v = graph.get_edge(parent[v]).from) {
      int edge_id = parent[v];
      graph.add_flow(edge_id, min_capacity);
    }

    // Add the flow in this augmenting path to the total flow
    flow += min_capacity;
  }

  return flow;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  FlowGraph graph = read_data();

  std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
  return 0;
}
