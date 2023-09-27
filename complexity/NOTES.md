# Complexity

## NP-Complete Problems

For thousands of practically important problems we don't have an efficient algorithm yet.

An efficient algorithm for one such problem automatically gives efficient algorithms for all of these problems.

### Search Problems

**Search Problem**: Given an instance of the problem, find a solution or report that none exists.

**Satisfiability**: Many hard problems are stated in terms of SAT naturally. Given a boolean formula, is there an assignment of variables that makes the formula true?

One must be able to check quickly whether a solution $S$ is indeed a solution for $I$; that is, in time polynomial in the length of $I$. In particular, the length of $S$ should be polynomial in the length of $I$.

A few practical search problems for which polynomial algorithms remain unknown:

#### Travelling Salesman Problem (TSP)

Input: Pairwise distances between $n$ cities and a budget $b$.

Output: A cycle that visits each city *exactly once* and has total length at most $b$.

TSP is usually stated as an *optimisation problem*; that is, find the shortest cycle. The search problem guarantees that a solution exists.

- Checking all permutations runs in $O(n!)$ time and is extremely slow.
- Dynamic programming runs in $O(n^2 2^n)$ time and is still too slow.
- No significantly better upper bound is known.

The TSP is an extension of the MST with an additional constraint:

| Minimum Spanning Tree (MST) Problem | TSP |
| --- | --- |
| Decision problem: Given $n$ cities, connect them by $(n-1)$ roads of minimal total length. | Decision problem: Given $n$ cities, connect them *in a path* by $(n-1)$ roads of minimal total length. |
| Can be solved efficiently. | No polynomial-time algorithm is known. |

#### Hamiltonian Cycle Problem

|  | Eulerian Cycle Problem | Hamiltonian Cycle Problem |
| --- | --- | --- |
| Input | A graph. | A graph. |
| Output | A cycle that visits each *edge* of the graph exactly once. | A cycle that visits each *vertex* of the graph exactly once. |
| Solution | Can be solved efficiently. | No known polynomial-time algorithm. |

A graph has an Eulerian cycle if and only if it is connected and the degree of each vertex is even.

#### Longest Path Problem

Input: A weighted graph, two vertices $s, t$, and a budget $b$.

Output: A simple path (containing no repeated vertices) of total length at least $b$ from $s$ to $t$.

|  | Shortest Path Problem | Longest Path Problem |
| --- | --- | --- |
| Input | A weighted graph, two vertices $s, t$, and a budget $b$. | A weighted graph, two vertices $s, t$, and a budget $b$. |
| Output | A simple path (containing no repeated vertices) of total length *at most* $b$ from $s$ to $t$. | A simple path (containing no repeated vertices) of total length *at least* $b$ from $s$ to $t$. |
| Solution | Can be solved efficiently. | No known polynomial-time algorithm. |

#### Integer Linear Programming Problem

|  | Linear Programming Problem | Integer Linear Programming Problem |
| --- | --- | --- |
| Input | A set of linear inequalities $Ax \leq b$. | A set of linear inequalities $Ax \leq b$. |
| Output | A *real* point $x$ that satisfies all inequalities. | An *integer* point $x$ that satisfies all inequalities. |
| Solution | Can be solved efficiently. | No known polynomial-time algorithm. |

#### Independent Set Problem

|  | Independent Set in a Tree | Independent Set in a Graph |
| --- | --- | --- |
| Input | A *tree* $T$ and a budget $b$. | A *graph* $G$ and a budget $b$. |
| Output | A set of vertices of size at least $b$ that are pairwise non-adjacent (i.e. no two of them are adjacent). | A set of vertices of size at least $b$ that are pairwise non-adjacent (i.e. no two of them are adjacent). |
| Solution | Can be solved efficiently. | No known polynomial-time algorithm. |

### P and NP

| Class P | Class NP |
| --- | --- |
| Problems whose solutions can be *found* efficiently (i.e., in polynomial time). | Problems whose solutions can be *verified* efficiently (i.e., in polynomial time). |
| - MST | - TSP |
| - Shortest Path | - Longest Path |
| - Linear Programming | - Integer Linear Programming |
| - IS on trees | - IS on graphs |

- If $P = NP$, then all search problems can be solved in polynomial time.
- If $P \neq NP$, then there exist search problems that cannot be solved in polynomial time.

We will show that the satisfiability problem, the travelling salesman problem, the independent set problem, the integer linear programming problem are the hardest problems in NP.

### Reductions

A search problem $A$ is reduced to a search problem $B$ (written $A \rarr B$) if a polynomial-time algorithm for $B$ can be used to solve $A$ in polynomial time.

That is, if there exists a polynomial-time algorithm $f$ that converts any instance $I$ of $A$ into an instance $f(I)$ of $B$, together with a polynomial-time algorithm $h$ that converts any solution $S$ of $f(I)$ back into a solution $h(S)$ of instance $I$ of $A$. If there is no solution to $f(I)$, then there is no solution to $I$.

**NP-Completeness**: A search problem is NP-complete if all other search problems reduce to it.

### Showing NP-Completeness

$A \rarr B$:

- If $B$ is easy (and can be solved in polynomial time), then so is $A$.
- If $A$ is hard (and cannot be solved in polynomial time), then so is $B$.

Reductions compose: if $A \rarr B$ and $B \rarr C$, then $A \rarr C$.

Therefore, if $A \rarr B$ is NP-complete, then so is $B$.

Question: Assume that a search problem $A$ is NP-complete and a search problem $B$ reduces to $A$ (that is, $B \rarr A$). Does this mean that $B$ is also NP-complete?

No. The problem $A$ is NP-complete, meaning that all other search problems reduce to it - in particular, the problem $B$. Hence the fact that $B$ reduces to $A$ does not tell us anything new. To prove that $B$ is NP-complete, we would need to reduce $A$ to $B$.

#### Independent Set to Vertex Cover

|  | Independent Set | Vertex Cover |
| --- | --- | --- |
| Input | A graph $G$ and a budget $b$. | A graph $G$ and a budget $b$. |
| Output | A subset of *at least* $b$ vertices such that no two of them are adjacent. | A subset of *at most* $b$ vertices that touch every edge. |

$I$ is an independent set of $G(V, E)$ if and only if $V - I$ is a vertex cover of $G$.

Reduction from IS to VC: to check whether $G(V, E)$ has an independent set of size at least $b$, check whether $G$ has a vertex cover of size at most $\lvert V \rvert - b$:

- $f(G(V, E), b) = (G(V, E), \lvert V \rvert - b)$
- $h(S) = V - S$

#### 3-SAT to Independent Set

#### SAT to 3-SAT

#### Circuit SAT to SAT

#### All of NP to Circuit SAT

### Dealing with NP-Completeness

#### Using SAT-Solvers

Theory: We have no efficient algorithm checking satisfiability.

Practice: SAT-Solvers routinely solve instances with thousands of variables.

#### [Minisat](https://msoos.github.io/cryptominisat_web/)

```bash
sudo apt-get update && sudo apt-get install minisat
```

#### Special Cases

##### 2-SAT

##### Independent Sets in Trees

#### Exact Algorithms

##### 3-SAT: Backtracking

##### 3-SAT: Local Search

##### TSP: Dynamic Programming

##### TSP: Branch and Bound

#### Approximation Algorithms

##### Vertex Cover

##### Metric TSP

##### TSP: Local Search
