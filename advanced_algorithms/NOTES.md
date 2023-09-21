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

## Linear Programming

Given some real numbers $x_1, x_2, \dots, x_n$ satisfying some linear inequalities

$$
a_{11}x_1 + a_{12}x_2 + \dots + a_{1n}x_n \leq b_1 \\
a_{m1}x_1 + a_{m2}x_2 + \dots + a_{mn}x_n \leq b_m
$$

maximise (or minimise) some linear objective function

$$
v_1x_1 + v_2x_2 + \dots + v_nx_n
$$

Input: An $m \times n$ matrix $A$ and vectors $b \in \R^m, v \in \R^n$

Output: A vector $x \in \R^n$ s.t. $Ax \leq b$ and $v^Tx$ is maximised (or minimised).

*Network flows are actually a special case of linear programming:*

$$
0 \leq f_e \leq C_e \forall e \\
\sum_{e \in \delta^-(v)} f_e - \sum_{e \in \delta^+(v)} f_e = 0 \forall v \neq s, t
$$

### Convexity

A linear equation defines a hyperplane. A linear inequality defines a half-space.

So a system of linear inequalities defines a region bounded by a bunch of hyperplanes.

A **polytope** is a region in $\R^n$ bounded by finitely many flat surfaces. These surfaces may intersect in lower-dimensional **facets** (like edges); with zero-dimensional facets called **vertices**.

But not every polytope is possible. Everything must be on one side of each face.

A region $C \subset \R^n$ is **convex** if for any $x, y \in C$ the line segment connecting $x$ and $y$ is contained in $C$.

An intersection of halfspaces is convex.

*The region defined by a system of linear inequalities is always a convex polytope.*

Let $C$ be a convex region and $x \notin C$ a point. Then there is a hyperplane $H$ separating $x$ from $C$.

A linear function on a polytope takes its minimum / maximum values on vertices.

In summary,

- a region determined by LP is always a convex polytope
- the optimum is always at a vertex
- the convex polytope can be separated from outside points by hyperplanes

### Duality

Given a (primal) linear program

$$
\min_{Ax \leq b}{v^Tx}
$$

the **dual linear program** is the linear programme

$$
\max_{y \geq 0, y^TA = v}{b^Ty}
$$

The dual bounds is the optimum for the primal. In fact, *a linear programme and its dual always have the same (numerical) answer.*

Consider such a primal and dual LP. Then in the solutions, $y_i \gt 0$ olny if the $i^{th}$ inequality is tight. So, the dual solution gives a certificate that the primal solution is optimal.

### LP Formulations

- Full Optimisation: Minimise or maximise a linear function subject to a system of linear inequality constraints (or say that the constraints have no solution).
- Optimisation from a Starting Point: Given a system of linear inequalities and a vertex of the polytope they define, optimise a linear function with respect to these constraints.
- Solution Finding: Given a system of linear inequalities, find some solution.
- Satisfiability: Given a system of linear inequalities, determine whether or not there is a solution.

**Equivalence:** Actually, if you can solve any of these problems, you can solve all of them.

Technical point: Things are a bit messier if some intermediate systems don't have optima.

Fix: Start with $n$ constraints (this gives a single vertex). Then while trying to add a constraint $v^Tx \geq t$, don't just maximise $v^Tx$, also add $v^Tx \leq t$ as a constraint - so that the maximum will exist.

Solution finding: How to find the best solution?

Duality: Instead of

$$
\min_{Ax \leq b}{v^Tx}
$$

instead find the solution to:

$$
Ax \leq b \\
y \geq 0 \\
y^TA = v \\
x^Tv = y^Tb
$$

This will give the optimal solution to the original problem.

### The Simplex Algorithm

The Simplex algorithm is one of the oldest algorithms for solving linear programmes, and still one of the most efficient - although the runtime is not quite what we would like.

- Vertex $p$ when $n$ defining equations are tight (solve with Gaussian elimination).
- Relax one equation to get an edge. Points of form $p + tw, t \geq 0$.
- Edge continues until it violates some other constraint.
- If $v^Tw \gt 0$, then $p + tw$ is better than $p$, i.e. can follow the edge to find a larger value of the objective.

Theorem: If $p$ is a vertex that is not optimal, there is some adjacent vertex that does better.

The runtime of the algorithm is proportional to the path length. Path length is usually pretty reasonable. However, there are examples where the path length is exponential in the number of variables.

**Degeneracy:** If more than $n$ constraints are tight, i.e. more than $n$ hyperplanes intersect at a vertex, then the vertex is degenerate. This can cause the Simplex algorithm to get stuck in a loop, not knowing which equation to relax.

Fix: Tweak equations a bit to avoid these intersections, by making infinitesimal changes: Strengthen first by $\epsilon$, next by $\epsilon^2$, etc.

In summary, the Simplex algorithm

- solves LPs
- works well most of the time
- but may be exponential in some cases

### The Ellipsoid Algorithm

- solves LPs
- can run with only a separation oracle
- runs in polynomial time in all cases, i.e. has better worst-case performance then simplex
- but in practice is actually often slower

The algorithm:

1. Relax all equations a bit.
2. Bound solution set in large ball.
3. Given this ellipsoid that contains all solutions, see if the centre of the ellipsoid is a solution.

    (a) If it is a solution, the system is satisfiable.
