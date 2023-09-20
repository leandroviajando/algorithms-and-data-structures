# Advanced Algorithms

## Network Flows

A **network** is a directed graph $G$ with:

- Each edge, $e$, is assigned a positive real capacity, $C_e$.
- One (or more) vertices are labelled a **source**.
- One (or more) vertices are labelled a **sink**.

With flows, rather than talking about where each car goes, we will instead concern ourselves with the total flow, $f_e$, through each edge $e$. This must satisfy two conditions:

- **Rate limitation**: For each edge $e$, $0 \leq f_e \leq C_e$.
- **Conservation of flow**: For all vertices $v$ other than the source and sink, the total flow into $v$ must equal the total flow out of $v$: $\sum_{e \in \delta^-(v)} f_e = \sum_{e \in \delta^+(v)} f_e$.

Thus, a **flow** in a network is an assignment of a real number flow, $f_e$, to each edge $e$ so that:

- $0 \leq f_e \leq C_e \forall e$
- $\sum_{e \in \delta^-(v)} f_e = \sum_{e \in \delta^+(v)} f_e \forall v \neq s, t$

For a flow, $f$, its **size** is given by the sum of flows out of a source (or sink) minus the sum of lows going into a source (or sink): $|f| = \sum_{e \in \delta^+(s)} f_e - \sum_{e \in \delta^-(s)} f_e$.

**Maxflow** problem: How large a flow can fit through a network?

Input: A network $G$

Output: A flow $f$ for $G$ with $\lvert f \rvert$ as large as possible.

### Residual Networks

Given a network $G$ and flow $f$, the **residual network** $G_f$ is a directed graph with places where flow can still be added to $f$, including places where existing flow can be cancelled.

For each edge $e$ of $G$, $G_f$ has edges:

- $e$ with capacity $C_e - f_e$ (unless $f_e = C_e$)
- opposite $e$ with capacity $f_e$ (unless $f_e = 0$)

**Residual flow**: Given a network $G$ and flow $f$; any flow $g$ on $G_f$ can be added to $f$ to get a new flow on $G$:

- $g_e$ adds to $f_e$
- $g_{e'}$ subtracts from $f_e$

Theorem: Given $G$, $f$, $G_f$ and $g$ as above, then

- $f + g$ is a flow on $G$.
- $\lvert f + g \rvert = \lvert f \rvert + \lvert g \rvert$.
- all flows on $G$ are of this form for some $g$.

### Maxflow-Mincut

In order to find maxflows, we need a way of verifying that they are optimal. In particular, we need techniques for bounding the size of the maxflow, to find a **bottleneck** that needs to be crossed.

Given a network $G$, a **cut** $C$ is a set of vertices of $G$ so that $C$ contains all sources of $G$ and no sinks of $G$. The *size* of a cut is given by the sum of capacities of edges out of $C$: $\lvert C \rvert = \sum_{e \in \delta^+(C)} C_e$.

A cut provides an upper bound on the flow of a network: For any flow $f$ and any cut $C$ in a network $G$, $\lvert f \rvert \leq \lvert C \rvert$.

In other words, for any cut $C$, we get an upper bound on the maxflow of $G$: $Maxflow \leq \lvert C \rvert$.

For any network $G$,

$$
\max_{\text{flows } f}{\lvert f \rvert} = \min_{\text{cuts } C}{\lvert C \rvert}
$$

*There is always a cut small enough to give the correct upper bound.*

We have found an $f$ and $C$ s.t. $\lvert f \rvert = \lvert C \rvert$. By the above lemma, cannot have larger $\lvert f \rvert$ or smaller $\lvert C \rvert$. So $\max{\lvert f \rvert} = \min{\lvert C \rvert}$. This is called a **maxflow-mincut** pair.

Therefore, can always check if flow is maximal by finding the maximum cut. If $\lvert f \rvert = \lvert C \rvert$, then $f$ is maximal.

### The Ford-Fulkerson Algorithm

- Start with zero flow.
- Repeatedly add flow.
- Stop when you cannot add more.

Adding flow:

- Compute residual network $G_f$.
- Find flow $g$ for $G_f$ with $\lvert g \rvert \gt 0$.
- Replace $f$ with $f + g$ ($\lvert f + g \rvert \gt \lvert f \rvert$).

If there is a path, add flow along the path. If there's no source-sink path in $G_f$, then $f$ is a maxflow.

```c++
void ford_fulkerson(Graph G, Vertex s, Vertex t) {
  Flow f = zero_flow(G);
  while (true) {
    Graph Gf = residual_network(G, f);
    Flow g = find_augmenting_path(Gf, s, t);
    if (g == zero_flow(G))
      break;

    f = f + g;
  }
  return f;
}
```

$G_f$ can be computed in $O(\lvert E \rvert)$ time. Each time, increase total flow by at least $1$. So, the **runtime** of the algorithm is $O(\lvert E \rvert \lvert f^{*}\rvert)$, where $f^{*}$ is the size of the maxflow.

- This is potentially quite large if the size of the flow $\lvert f \rvert$ is numerically large.
- It is **non-deterministic** - there may be many augmenting paths to choose from. The choice of augmenting path can affect the runtime.

Fortunately, the Ford-Fulkerson algorithm gives us a choice as to which augmenting path to use.

### The Edmonds-Karp Algorithm

The Edmonds-Karp algorithm always chooses the *shortest* (in terms of number of edges) augmenting path, by using a **breadth-first search** instead of a depth-first search.

As the Edmonds-Karp algorithm executes, for any vertex $v \in V$ the distance $d_{G_f}(s, v)$ only increases. Similarly, $d_{G_f}(v, t)$ and $d_{G_f}(s, t)$ can only increase.

Therefore, when running the Edmond-Karp algorithm, if an edge $e$ is saturated, it will not be used in an augmenting path again, until $d_{G_f}(s, t)$ increases.

$d_{G_f}(s, t)$ can only increase $\lvert V \rvert$ times. Each time can only have $O(\lvert E \rvert)$ many saturated edges and, hence, only $O(\lvert V \rvert \lvert E \rvert)$ many augmenting paths. Each path takes $O(\lvert E \rvert)$ time. So, the **runtime** of the Edmonds-Karp algorithm is $O(\lvert V \rvert \lvert E \rvert^2)$.

Thus, choosing augmenting paths based on path length alleviates the runtime dependence on the numerical sizes of edge capacities.

There are in fact even more complicated algorithms. The state of the art is $O(\lvert V \rvert \lvert E \rvert)$.

### Applications

#### Bipartite Matching

Input: Bipartite graph $G$.

Output: A matching on $G$ consisting of as many edges as possible (ideally pairing up all the vertices).

Connection to Flows:

- Need to connect nodes on left to nodes on right without putting too many connections through any given node.
- Have source connect to left nodes.
- Have right nodes connect to sink.

A **bipartite graph** is a graph $G = (V, E)$ whose vertex set is partitioned into two subsets, $U$ and $V$, so that all edges are between a vertex of $U$ and a vertex of $V$.

Let $G$ be a bipartite graph and $G'$ the corresponding network. There is a $1 - 1$ correspondence between matchings on $G$ and integer-valued flows on $G'$.

Koenig's Theorem: For a bipartite graph $G$, if $k$ is the size of the maximal matching, there is a set $S$ of $k$ vertices so all edges of $G$ are adjacent to $S$.

Note that if you can find such an $S$, the maximal matching has size at most $\lvert S \rvert$.

The Marriage Lemma: Let $G$ be a bipartite graph with $n$ vertices on either side. Then there is a perfect pairing on $G$ (a matching using all vertices) unless there is some set, $S$ of $m$ vertices of $U$, s.t. the total number of vertices adjacent to a vertex in $S$ is less than $m$.

#### Image Segmentation

- Construct corresponding network $G$
- Compute a maxflow $f$ for $G$
- Compute residual $G_f$
- Let $C$ be the collection of vertices reachable from $s$ in $G_f$
