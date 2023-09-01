# Graph Algorithms

## Graph Decomposition

A graph represents connections between objects. This is useful to describe many important phenomena, e.g. the internet (web pages connected by links), maps (roads), social networks, etc.

An (undirected) graph is a collection $V$ of **vertices**, and a collection $E$ of **edges** each of which connects a pair of vertices.

**Loops** connect a vertex to itself; and there may also be **multiple edges** between the same vertices. If a graph has neither, it is called a **simple** graph.

### Graph Representation

For many problems, the adjacency list will be the most efficient representation.

| Operation | Adjacency Matrix | Edge List | Adjacency List |
| --- | --- | --- | --- |
| `Is Edge?` | $\Theta(1)$ | $\Theta(\lvert E \rvert)$ | $\Theta(deg)$ |
| `List Edge` | $\Theta(\lvert V \rvert^2)$ | $\Theta(\lvert E \rvert)$ | $\Theta(\lvert E \rvert)$ |
| `List Neighbours` | $\Theta(\lvert V \rvert)$ | $\Theta(\lvert E \rvert)$ | $\Theta(deg)$ |

Note graph algorithm **runtimes** depend on both $\lvert V \rvert$ and $\lvert E \rvert$.

So which is faster, $O(\lvert V \rvert^{\frac{3}{2}})$ or $O(\lvert E \rvert)$?

A graph's **density** is the number of edges in terms of the number of vertices:

- In **dense graphs**, a large fraction of pairs of vertices are connected by edges: $\lvert E \rvert \approx \lvert V \rvert^2$
- In **sparse graphs**, each vertex has only a few edges: $\lvert E \rvert \approx \lvert V \rvert$

### Undirected Graphs

#### Reachability

A **path** in a graph $G$ is a sequence of vertices $v_0, v_1, \dots, v_n$ so that for all $i, (v_i, v_{i+1})$ is an edge of $G$.

**Reachability:**

- Input: Graph $G$ and vertex $s$
- Visit markers: To keep track of vertices found, give each vertex a boolean `visited(v)`
- Explore edges in a depth-first ordering: Follow along a path, only backtracking once hit a dead end
- Output: The collection of vertices $v$ of $G$ so that there is a path from $s$ to $v$

Note unless you have an adjacency list representation, this algorithm isn't that efficient.

#### Depth-First Search (DFS)

Number of calls to `explore`:

- Each explored vertex is marked visited.
- No vertex is explored after visited once.
- Each vertex is explored exactly once.

Checking for neighbours:

- Each vertex checks each neighbour
- Total number of neighbours over all vertices is $\lvert E \rvert$

Total runtime: $O(\lvert V \rvert + \lvert E \rvert)$

- $O(1)$ per vertex for marking visited
- $O(1)$ per edge for checking neighbours

#### Connectivity

The vertices of a graph $G$ can be partitioned into **connected components** so that $v$ is reachable from $w$ if and only if they are in the same connected component.

*Proof:* Need to show that reachability is an **equivalence relation.**

- $v$ is reachable from $v$ (*reflexive*).
- If $v$ is reachable from $w$, then $w$ is reachable from $v$ (*symmetric*).
- If $v$ is reachable from $w$ and $w$ is reachable from $x$, then $v$ is reachable from $x$ (*transitive*).

**Connected Components:**

- Input: Graph $G$
- Idea: `explore(v)` finds all vertices reachable from $v$, i.e. its connected component; just need to repeat to find other components
- Output: The connected components of $G$

```c++
void explore(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &component, int u, int component_number) {
  visited[u] = true;
  component[u] = component_number;

  for (int v : adj[u])
    if (!visited[v])
      explore(adj, visited, component, v, component_number);
}

vector<int> number_of_components(vector<vector<int>> &adj) {
  vector<int> component(n, -1);  // Initialize component vector with -1 (no component assigned).

  int component_number = 0;
  vector<bool> visited(adj.size(), false);
  for (int u = 0; u < adj.size(); u++)
    if (!visited[u]){
      explore(adj, visited, component, u, component_number);
      component_number++;
    }

  return component;
}
```

#### Previsit and Postvisit Orderings

```c++
void previsit(int u) {
  pre(u) = clock;
  clock++;
}
void postvisit(int u) {
  post(u) = clock;
  clock++;
}

void explore(vector<vector<int>> &adj, vector<bool> &visited, int u) {
  visited[u] = true;

  previsit(u);
  for (int v : adj[u])
    if (!visited[v])
      explore(adj, visited, v);
  postvisit(u);
}
```

Previsit and postvisit numbers tell us about the execution of DFS: For any vertices $u, v$, the intervals $[pre(u), post(u)]$ and $[pre(v), post(v)]$ are either entirely *disjoint*, or one is contained in the other (i.e. they are in the same connected component).

### Directed Graphs

For example, one-way roads, links between web pages, followers on social networks, dependencies between tasks.

Can still run **DFS** on directed graphs:

- Only follow *directed* edges.
- `explore(v)` finds all vertices reachable from $v$.
- Can still compute previsit and postvisit orderings.

#### Directed Acyclic Graphs (DAGs)

A **cycle** in a graph $G$ is a sequence of vertices $v_1, v_2, \dots, v_n$ so that $(v_1, v_2), (v_2, v_3), \dots, (v_{n-1}, v_n), (v_n, v_1)$ are all edges of $G$.

If $G$ contains a cycle, it is called a **cyclic** graph; and it cannot be linearly ordered.

A directed graph $G$ is a **directed acyclic graph (DAG)** if it contains *no cycles*. Any DAG *can be linearly ordered*.

#### Topological Sort

In order to linearly order a directed graph, it needs to be a DAG.

A **source** is a vertex with no incoming edges. A **sink** is a vertex with no outgoing edges. The last vertex in a topological sort ordering must be a sink.

Idea:

- Find the sink by following the path as far as possible.
  - If there is no sink, the graph has a cycle.
- Put it at the end of the order.
- Remove it from the graph.
- Repeat. Runtime $O(\lvert V \rvert^2)$ - inefficient
  - Instead only back up as far as necessary to find a new sink.

*This is just DFS - the postvisit ordering is a topological sort.*

```c++
std::vector<int> toposort(vector<vector<int>> &adj) {
  std::vector<bool> used = std::vector<bool>(adj.size(), false);
  std::vector<int> order;

  for (int u = 0; u < adj.size(); u++)
    if (!used[u])
      dfs(adj, used, order, u);

  return order;
}
```

#### Strongly Connected Components

Two vertices $v, w$ in a directed graph are connected if you can reach $v$ from $w$ and $w$ from $v$.

Thus, a directed graph's vertices can be partitioned into strongly connected components - where two vertices are connected if and only if they are in the same component.

The **metagraph** (of the connected components) describes how SCCs connect to each other. It is a DAG.

In fact, the *metagraph of any graph* $G$ *is always a DAG*. Proof: Suppose not. So there must be a cycle. Any nodes in the cycle can reach any others. So they should all be in the same SCC. Proved by contradiction.

Runtime: $O(\lvert V \rvert + \lvert E \rvert)$
