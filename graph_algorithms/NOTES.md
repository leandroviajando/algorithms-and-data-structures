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

## Paths in Graphs

### Breadth-First Search (BFS)

A **path length** $L(P)$ is the number of edges in a path. The **distance** between two vertices is the length of the shortest path between them.

Vertices and shortest paths between them can be represented with **distance layers**.

This is how BFS works, and it can be implemented with a queue.

The **running time** of BFS is $O(\lvert V \rvert + \lvert E \rvert)$. Proof:

- Each vertex is enqued at most once.
- Each edge is examined either once (for directed graphs) or twice (for undirected graphs).

#### Shortest Path Tree

The distance layers can be represented as a shortest path tree.

The tree of shortest paths can be built from one origin vertex $s$ by running BFS from $s$.

The tree can then be used to reconstruct the optimal path from any vertex $v$ to $s$, in $O(\lvert V \rvert + \lvert E \rvert)$ time.

### Fastest Route

An algorithm to find the shortest
paths from a single node to all the nodes in a graph *with non-negative edge weights*.

#### Naive Algorithm

Any subpath of an optimal path is optimal.

**Edge relaxation** checks if $d(v) > d(u) + w(u, v)$, then $d(v) = d(u) + w(u, v)$; giving an upper bound on the distance from $s$ to $v$.

A naive algorithm would be to relax all edges $n-1$ times, giving a runtime of $O(\lvert V \rvert \lvert E \rvert)$.

#### [Dijkstra's Algorithm](https://www.coursera.org/learn/algorithms-on-graphs/lecture/ZS5pm/dijkstra-example)

Maintain a set $R$ of vertices for which `dist` is already set correctly (the "known region").

The first vertex added to $R$ is $s$.

On each iteration, take a vertex outside of $R$ with the smallest `dist` value, add it to $R$, and relax all its outgoing edges.

Dijktra's algorithm can be [implemented](https://www.coursera.org/learn/algorithms-on-graphs/lecture/cgiHK/implementation) with a **priority queue**.

With an **array** priority queue, the running time is $O(V) + T(MakeQueue) + \lvert V \rvert \times T(ExtractMin) + \lvert E \rvert \times T(ChangePriority) = O(\lvert V \rvert + \lvert V \rvert + \lvert V \rvert^2 + \lvert E \rvert) = O(\lvert V \rvert^2)$.

With a **binary heap** priority queue, the running time is: $O(\lvert V \rvert + \lvert V \rvert + \lvert V \rvert \log \lvert V \rvert + \lvert E \rvert \log \lvert V \rvert) = O( ( \lvert V \rvert + \lvert E \rvert ) \log \lvert V \rvert )$.

*Note depending on the number of edges and vertices of the graph, the array or binary heap implementation may be faster*.

For example, if $\lvert E \rvert \approx \lvert V \rvert^2$, then the array implementation is faster.

### Currency Exchange

Input: Currency exchange graph with weighted directed edges $e_i$ between some pairse of currencies with weights $r_{e_i}$ corresponding to the exchange rate.

Output: Maximise $\prod_{j=1}^k{r_{e_j}} = r_{e_1}r_{e_2} \dots r_{e_k}$ over paths $(e_1, e_2, \dots, e_k)$ from USD to RUR in the graph.

#### Reduction to Shortest Paths

- To replace the product with a sum, take the logarithm of the weights: $\log{r_{e_1}} + \log{r_{e_2}} + \dots + \log{r_{e_k}}$.
- To solve a minimisation problem instead of a maximisation problem, negate the weights: $-\log{r_{e_1}} - \log{r_{e_2}} - \dots - \log{r_{e_k}}$.

Problem: Dijkstra's algorithm doesn't work with negative weights. It relies on the fact that a shortest path from $s$ to $t$ goes only through vertices that are closer to $s$ than $t$. But with negative edge weights, this doesn't hold. So when adding the next vertex to $R$, there may be a shorter path to it through a vertex that is not yet in $R$.

#### Bellman-Ford Algorithm

The Bellman-Ford algorithm is a general algorithm for finding shortest spots in any weighted graphs, incl. negative weighted edges, although no negative cycles (which would result in negative infinity, see below).

The Bellman-Ford algorithm actually relies on the previously seen naive algorithm for shortest paths, which, it turns out, works with negative weights.

Its running time is thus $O(\lvert V \rvert \lvert E \rvert)$.

##### Negative Cycles

A graph $G$ contains a negative weight cycle if the $\lvert V \rvert$th iteration of the Bellman-Ford algorithm updates some `dist` value.

The Bellman-Ford algorithm can thus be used to find a negative cycle in a graph.

##### Infinite Arbitrage

It is possible to get any amount of currency $u$ from currency $S$ if and only if $u$ is reachable from some node $w$ for which `dist[w]` decreased on iteration $\lvert V \rvert$.

## Minimum Spanning Trees

Input: A connected, undirected graph $G = (V, E)$ with positive edge weights $w_e$.

Output: A subset of edges $E' \subseteq E$ of minimum total weight that connects all vertices, i.e. such that the graph $(V, E')$ is connected.

A **tree** is an undirected graph that is connected and acyclic. A tree of $n$ vertices has $n-1$ edges.

Any connected undirected graph $G(V, E)$ with $\lvert E \rvert = \lvert V \rvert - 1$ is a tree.

*An undirected graph is a tree iff there is a unique path between any pair of its vertices.*

Therefore, an optimal solution to this problem will in fact be a tree.

### Building a Network

For example, assume that we have six machines in our office and we would like to join them by putting wires between some pairs of them such that each machine is reachable from any other machine.

### Greedy Algorithms

| Kruskal's Algorithm | Prim's Algorithm |
| --- | --- |
| repeatedly add the next lightest edge if this doesn't produce a cycle | repeatedly attach a new vertex to the current tree by a lightest edge |
| use disjoint sets to check whether the current edge joins two vertices from different components | use a priority queue to quickly find the next lightest edge |
| works well when the graph is sparse (i.e. there are relatively few edges compared to the number of vertices) | works well when the graph is dense (i.e. there are many edges compared to the number of vertices) |

### Cut Property

Let $X \subseteq E$ be a part of a MST of $G(V, E), S \subseteq V$ be such that no edge $X$ crosses between $S$ and $V - S$, and $e \in E$ be a lightest edge across this partition. Then $X + \{e\}$ is a part of some MST.

### Kruskal's Algorithm

- Repeatedly add to $X$ the next lightest edge $e$ that doesn't produce a cycle.
- At any point of time, the set $X$ is a forest, that is, a collection of trees.
- The next edge $e$ connects two different trees - say $T_1$ and $T_2$.
- The edge $e$ is the lightest edge between $T_1$ and $V - T_1$, hence adding $e$ is safe, by the cut property.

Implementation details:

- Use the disjoint sets data structure.
- Initially, each vertex lies in a separate set.
- Each set is the set of vertices of a connected component.
- To check whether the current edge $\{u, v\}$ produces a cycle, check whether $u$ and $v$ belong to the same set.

Running time:

- Sorting edges: $O(\lvert E \rvert \log \lvert E \rvert) = O(\lvert E \rvert \log \lvert V \rvert^2) = O(2 \lvert E \rvert \log \lvert V \rvert) = O(\lvert E \rvert \log \lvert V \rvert)$
- Processing edges: $2 \lvert E \rvert \times T(Find) + \lvert V \rvert \times T(Union) = O((\lvert E \rvert + \lvert V \rvert) \log \lvert V \rvert) = O(\lvert E \rvert \log \lvert V \rvert)$
- Total: $O(\lvert E \rvert \log \lvert V \rvert)$

### Prim's Algorithm

- $X$ is always a subtree, grows by one edge at each iteration.
- Add a lightest edge between a vertex of the tree and a vertex not in the tree.
- Very similar to Dijkstra's algorithm, uses "priority" (compare with Dijkstra's "cost").

Running time:

- $O(\lvert V \rvert \times T(ExtractMin) + \lvert E \rvert \times T(ChangePriority)) = O((\lvert V \rvert + \lvert E \rvert) \log \lvert V \rvert) = O(\lvert E \rvert \log \lvert V \rvert)$

Running time for array-based implementation:

- $O(\lvert V \rvert + \lvert V \rvert^2 + \lvert E \rvert) = O(\lvert V \rvert^2)$

## Advanced Shortest Paths - Advancements on Dijkstra's Algorithm

### Bidirectional Dijkstra's Algorithm

#### Bidirectional Search

Consider again the shortest path problem:

Input: A graph $G$ with *non-negative* edge weights, a source vertex $s$ and a target vertex $t$.

Output: The shortest path between $s$ and $t$.

Dijkstra's algorithm ($O(( \lvert E \rvert + \lvert V \rvert ) \log \lvert V \rvert )$) is pretty fast, but it still has to explore a lot of vertices and edges. For a graph of the USA with 20M vertices and 50M edges it will take several seconds on average - too slow for many applications, i.e. Google Maps.

#### Six Handshakes

#### Bidirectional Dijkstra

#### Finding the Shortest Path after Meeting in the Middle

#### Computing the Distance

### A-Star (A*) Algorithm

#### Performance

#### Bidirectional A*

#### Potential Functions and Lower Bounds

#### Landmarks

### Contraction Hierarchies

#### Highway Hierarchies and Node Importance

#### Preprocessing

#### Witness Search

#### Query

#### Proof of Correctness

#### Node Ordering
