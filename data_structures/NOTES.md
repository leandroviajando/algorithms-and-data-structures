# Data Structures

## Basic Data Structures

### Arrays

An array is

- a contiguous area of memory
- consisting of equal-size elements
- indexed by contiguous integers.

For example, an array whose

- address is 1000,
- element size is 8,
- first index is 0

has its elements stored at locations `1000`, `1008`, `1016`, `1024`, `1032`, `1040`, `1048`, etc. in memory.

Hence, its **API operations** take

- constant time for read and write **random access** to any element
- constant time to add / remove at the end
- but linear time to add / remove at an arbitrary location

Arrays are usually laid out in **row-major order**, although may also be in column-major order. For example, a three-dimensional array with the first element at indices `(1, 1, 1)` has the next element at `(1, 1, 2)` in the case of row-major order, or at `(2, 1, 1)` with column-major order.

### Linked Lists

Every node contains a `key` and a `next` pointer.

List elements need not be contiguous. Hence, it takes

- constant time to insert at or remove from the front.
- with tail and doubly-linked lists, constant time to insert at or remove from the back.
- $O(n)$ time to find an arbitrary element
- with doubly-linked lists, constant time to insert between nodes or remove a node

|  | Singly-Linked List | with tail | Doubly-Linked List | with tail |
| --- | --- | --- | --- | --- |
| PushFront(Key) | $O(1)$ | | $O(1)$ | |
| TopFront() | $O(1)$ | | $O(1)$ | |
| PopFront() | $O(1)$ | | $O(1)$ | |
| PushBack(Key) | $O(n)$ | $O(1)$ | $O(n)$ | $O(1)$ |
| TopBack() | $O(n)$ | $O(1)$ | $O(n)$ | $O(1)$ |
| PopBack() | $O(n)$ | | $O(1)$ | |
| Find(Key) | $O(n)$ | | $O(n)$ | |
| Erase(Key) | $O(n)$ | | $O(n)$ | |
| Empty() | $O(1)$ | | $O(1)$ | |
| AddBefore(Node, Key) | $O(n)$ | | $O(1)$ | |
| AddAfter(Node, Key) | $O(1)$ | | $O(1)$ | |

### Stacks

**LIFO:**

| Operation | Description | Time complexity |
| --- | --- | --- |
| `push(key)` | adds key to collection | $O(1)$ |
| `key top()` | returns most recently added key | $O(1)$ |
| `key pop()` | removes and returns most recently added key | $O(1)$ |
| `bool empty()` | are there any elements in the stack? | $O(1)$ |

Stacks can be implemented with either an array or a linked list:

- The downside, for arrays, is that you have potentially space that you've over-allocated to allow for a stack to grow to a maximum size.
- For arrays, stacks have a maximum size.
- For linked lists, they don't have a maximum size.

### Queues

**FIFO:**

| Operation | Description | Time complexity |
| --- | --- | --- |
| `enqueue(key)` | adds key to collection | $O(1)$ |
| `key dequeue()` | removes and returns least recently added key | $O(1)$ |
| `bool empty()` | are there any elements in the queue? | $O(1)$ |

Queues can be implemented with either a (singly-linked) linked list (with tail pointer) or an array (with a read and a write pointer).

One distinction, again, between the array and linked list implementations is that in the array implementation there is a maximum size that the queue can grow to, i.e. it's bounded.

### Trees

Each node contains

- `key`
- `children`: list of child nodes
- (optional) `parent`

**Tree Traversal:**

- **Depth-first:** completely traverse one sub-tree before exploring a sibling sub-tree
- **Breadth-first:** traverse all nodes at one level before progressing to the next level

--------------------

- **Pre-order:** evaluate the node itself before evaluating its children
- **In-order**
- **Post-order:** evaluate all children fully before evaluating a node itself

| Operation | Most suitable DS |
| --- | --- |
| random access in $O(1)$ | array |
| insert elements in middle in $O(1)$ | list |
| insert elements in the back and extract from the the front | queue |
| recursion | stack |
| directory structure of your hard drive | tree |

## Dynamic Arrays and Amortised Analysis

Static arrays' size is static:

```c++
int my_array[100];
```

Semi-solution: dynamically-allocated arrays:

```c++
int *my_array = new int[size];
```

Problem: might not know max size

Solution: Instead of storing a reference to the array, *store a pointer to a dynamically allocated (i.e. resizable) array, and replace it with a newly-allocated array as needed (i.e. when need to resize)*

Dynamic Array API:

- `Get(i)`: returns element at location `i*` in $O(1)$
- `Set(i, val)`: sets element `i` to `val*` in $O(1)$
- `PushBack(val)`: adds `val` to the end in $O(n)$ (worst case) or $O(1)$ (best case, see below)
- `Remove(i)`: removes element at location `i` in $O(n)$
- `Capacity()`: maximum number of elements until need to resize
- `Size()`: the number of elements

Dynamic Array Implementation:

- `arr`: dynamically allocated array
- `capacity`: size of the dynamically-allocated array
- `size`: number of elements currently in the array

If the dynamic array needs to be resized to accomodate a new element, it will take $O(n)$ to create a new array of double size and copy all the current elements into it. Otherwise, if the array's size is less than its capacity, pushing back a new element takes just constant time.

We only resize every so often, i.e. many $O(1)$ operations are followed by an $O(n)$ operation.

### Amortised Analysis

*What is the total of inserting many elements?*

Given a sequence of $n$ operations, the **amortised cost** is

$$
\frac{\text{Cost}(n \text{ operations})}{n}
$$

So let $c_i = \text{ cost of i'th insertion}$. Then, given that we always double the array size (i.e. the resize factor is 2) when resizing, we will need to resize for every power of 2'th insertion:

$$
c_i = 1 + \begin{cases}
  i-1 & \text{if } i-1 \text{ is a power of } 2 \\
  0 & \text{otherwise}
\end{cases}
$$

This gives the amortised cost for $n$ calls to `PushBack` of a dynamic array as:

$$
\frac{\sum_{i=1}^{n}{c_i}}{n} = \frac{n + \sum_{j=1}^{\lfloor \log_2(n-1) \rfloor}{2^j}}{n} = \frac{O(n)}{n}
$$

This is because, by the geometric series formula:

$$
\sum_{j=1}^{\lfloor \log_2(n-1) \rfloor}{2^j} = 2^{\lfloor \log_2(n-1) \rfloor + 1} - 2
$$

and

$$
2^{\lfloor \log_2(n-1) \rfloor + 1} = 2 \times 2^{\lfloor \log_2(n-1) \rfloor} \leq 2(n-1) = O(n)
$$

*Note not to use a constant amount when resizing*: if you were to add a constant amount, e.g. expand by 10 elements each time, instead of a resize factor, the amortised cost would be quadratic!

## Priority Queues and Disjoint Sets

### Priority Queues

C++'s `priority_queue`, Java's `PriorityQueue` and Python's `heapq` are implementations of the priority queue data structure:

- `Insert(p)`: adds a new element with priority `p`
- `ExtractMax()`: extracts an element with maximum priority

| | `Insert` | `ExtractMax` |
| --- | --- | --- |
| Unsorted array / list | $O(1)$ | $O(n)$ |
| Sorted array / list | $O(n)$ | $O(1)$ |
| Binary heap | $O(\log n)$ | $O(\log n)$ |

Some additional operations might be:

- `Remove(it)`: removes an element pointed by an iterator `it`
- `GetMax()`: returns an element with maximum priority (without changing the set of elements)
- `ChangePriority(it, p)`: changes the priority of an element pointed by `it` to `p`

### Binary Heaps

A heap is a tree-based data structure that satisfies the **heap property:**

- A **binary max-heap** is a binary tree (i.e. each node has zero, one or two children) where the value of each node has value greater than or equal to its children's values.
- A **binary min-heap** is a binary tree (i.e. each node has zero, one or two children) where the value of each node has value less than or equal to its children's values.

The `Insert` operation is handled with `SiftUp`, and the `ExtractMax` operation with `SiftDown` - which both run in $O(\text{tree height})$ time.

The height of a d-ary tree (where all nodes have `d` children) is $\log_d(n)$ and the running time of `SiftUp` is $O(\log_d(n))$. For a binary tree, $d=2$.

#### Complete Binary Trees

A binary tree is **complete** if all its levels are filled, except possibly the last one, which must be filled *from left to right*.

Keeping a binary tree complete has two advantages:

- A complete binary tree with $n$ nodes has height at most $O(\log n)$.
- It can easily be stored in an array.

### Heap Sort

A heap (for implementation of a priority queue) can be created in $n \log(n)$ time, where the $\log(n)$ `SiftDown` procedure is called for $O(n)$ nodes.

Note that this is in fact a pessimistic upper bound. Because many of the nodes closer to the root will not take logarithmic time to sift down. It can be shown that this actually runs in $O(n + \frac{1}{2}n + \frac{1}{3}n + \frac{1}{4}n + \dots) = O(2n)$ linear time.

An application is a **partial sort** of the $k$ largest of $n$ elements: build a heap and `ExtractMax` $k$ times. This can be solved in $O(n)$, if $k = O(\frac{n}{\log n})$ because then $O(k \log n) = O(n)$. (Recall also from course 1 that sorting is $O(n \log n)$.)

### Disjoint Sets

A disjoint-set data structure supports the following operations:

- `MakeSet(x)`: creates a singleton set `{x}`
- `Find(x)`: returns the ID of the set containing `x`, i.e. can compare `Find(x) == Find(y)`
- `Union(x, y)`: merges two sets containing `x` and `y`

#### Disjoint Sets represented as Trees

This data structure can be **represented efficiently as a tree:**

- Represent each set as a rooted tree
- The ID of a set is the root of the tree
- `parent[i ... k] = parent[i]` where `i` is the root node

#### Union by rank

When merging two trees, in order minimise tree height, *hang the shorter one under the root of the taller one* (which increases the resulting tree's height by max $1$ - if both have equal height)

To quickly find the height of a tree, keep track of of the heights of all subtrees in an array `rank[i ... n]` where `rank[i]` is the height of the subtree whose root is `i`

*Lemma:* The height of any tree in the forest is at most $log_2 n$.

*The union by rank heuristic guarantees that `Union` and `Find` work in time $O(\log n)$.*

#### Path Compression

```pseudocode
if i != parent[i]:
  parent[i] <- Find(parent[i])
return parent[i]
```

The **iterated logarithm** of $n$, $\log^* n$, is the number of times the logarithm function needs to be applied to $n$ before the result is less or equal than 1; i.e. at most $5$ for practical values of $n$:

| $n$ | $\log^* n$ |
| --- | --- |
| $1$ | $0$ |
| $2$ | $1$ |
| $\{3, 4\}$ | $2$ |
| $\{5, 6, ..., 16\}$ | $3$ |
| $\{17, ... , 2^{16}\}$ | $4$ |
| $\{2^{16}, ... 2^{2^{16}}\}$ | 5 |

Assume that initially the data structure is empty. We make a sequence of $m$ operations including $n$ calls to `MakeSet`.

Then, using both union by rank and path compression heuristics:

- the total running time is $O(m \log^* n)$
- the amortised time for a single operation is thus $O(\log^* n)$, where $n \leq 5$

## Hash Tables

A **Map** from a set $S$ of keys to a set $V$ of values is a data structure with methods `HasKey(key)`, `Get(key)`, `Set(key, value)`, where `key` $\in S$, `value` $\in V$.

*An implementation of a Set or a Map using hashing is called a* **hash table.**

Python's `dict` and Java's `HashMap` are examples of hash tables.

Another example are IP addresses.

### Direct Addressing

There are $2^{32}$ IPv4 addresses. So we can store all theses addresses in an array of length $2^32$. But how do we map each IP address to its index in the array? An IP address consists of four parts, each of which can be represented as a binary number:

```pseudocode
int(IP):
  return IP[1]*2^24 + IP[2]*2^16 + IP[3]*2^8 + IP[4]
```

Accessing each element in the array is thus $O(1)$.

Problem: Need $2^{32}$ bits in memory. With IPv6, $2^{128}$ - which won't fit in memory.

That is, in general, for a data set with size $\lvert S \rvert = N$, the memory requirement is $O(N)$; and this only feasible for smaller values of $N$.

Question: What is the size of the array needed to store integer keys with up to 12 digits using direct addressing? There are 10 integers (0 to 9), so $10^{12}$.

### Hash Functions

Hash functions achieve direct addressing with $O(m)$ memory:

For any set of objects $S$ and any integer $m\gt0$, a function $h : S \rarr \set{0, 1, \dots, m-1}$ is called a **hash function**, and $m$ is its **cardinality**.

Unfortunately, by the pigeonhole principle, it is impossible to get all different values if the number of objects $\lvert S \rvert > m$.

When this happens and $h(o_1) = h(o_2)$ although $o_1 \neq o_2$, this is a **collision.**

Therefore, the desirable properties of a hash function are:

- should be fast to compute
- small enough cardinality $m$
- <s>different values for different objects</s> small probability of collision

### Chaining

Chaining is a technique to implement a hash table with number of objects $n$, has function of cardinality $m$, and longest chain length $c$.

Given there will be collisions, instead of mapping a key to a value, **chaining** involves *mapping every key to a doubly-linked list of values, i.e. a chain.*

**Runtime asymptotics:** Let $c$ be the length of the longest chain. Then the running time of `HasKey`, `Get` and `Set` is $\Theta(c+1)$.

**Memory consumption:** Let $n$ be the number of different keys in the map and $m$ the cardinality of the hash function. Then the memory consumption for chaining is $\Theta(n+m)$:

- $\Theta(n)$ to store $n$ `(key, value)` pairs
- $\Theta(m)$ for array `Chains` of size $m$ containing the chains corresponding to each pair

### Designing Hash Functions

Objective: make $m$ and $c$ as small as possible, given restriction that $c \geq \frac{n}{m}$.

Question: What is the maximum possible chain length for a hash function $h(x) = x mod 1000 = x mod 10^3$ used with a hash table of size $1000$ for a universe of all integers with at most $12$ digits? When the values of the last $3$ digits are fixed, there are $10^9$ numbers with at most $12$ digits; that is, the maximum chain length is $10^9$.

Desired properties:

- deterministic! (random would give different values each time)
- fast to compute
- distribute keys well into different cells
- few collisions

Unfortunately, if the number of possible keys is big ($\lvert S \rvert \gg m$), for any hash function $h$ there is a bad input resulting in many collisions.

Remember QuickSort: It was slow (quadratic time) and adding a random pivot improved performance.

Solution: We cannot use a random hash function. But we can define family of hash functions, and then randomly select a function from the family.

Let $U$ be the universe, i.e. the set of all possible keys. A set of hash functions $H = \set{h : U \rarr \set{0, 1, 2, \dots, m-1}}$ is called a **universal family** if for any two keys $x, y \in U, x \neq y$ the probability of collision $P[h(x) = h(y)] \leq \frac{1}{m}$

The ratio $\alpha = \frac{n}{m}$ between the number of objects $n$ stored in the hash table and the size of the hash table $m$ is called **load factor.**

**Running time:** If $h$ is chosen randomly from a universal family, the average length of the longest chain $c$ $O(1+\alpha)$ where $\alpha = \frac{n}{m}$ is the load factor of the hash table. Then, any operation on the hash table runs on average in time $O(1 + \alpha)$.

Ideally, we want the load factor to be in the medium range from $0.5 \lt \alpha \lt 1$ because if it's bigger than one, we will have collisions, and if it's less than 0.5, at least half of the hash table is just wasted without any chains in it.

Memory can be controlled by setting $m$: Use $O(m) = O(\frac{n}{\alpha}) = O(n)$ memory to store $n$ keys.

Operations will run in time $O(1 + \alpha)$, which is $O(1)$ on average.

### Dynamic Hash Tables

What if the number of keys $n$ is unknown in advance?

Copy the idea of dynamic arrays: Resize the hash table when the load factor $\alpha$ becomes too large, e.g. $0.9$.

Similar to dynamic arrays, single rehashing takes $O(n)$ time, but amortised running time of each operation with a hash table is still $O(1)$ on average, because rehashing will be rare.

### Building a Universal Family of Hash Functions

For any prime number $p$, there exists a universal family $H_p = \set{h_p^{a, b}(x) = ((ax+b) \text{ mod } p) \text{ mod } m} \forall a, b : 1 \leq a \leq p-1, 0 \leq b \leq p-1$ for the set of integers between $0$ and $p-1$.

The size of such a hash family (i.e. the number of different hash functions in the set) is $p(p-1)$.

For any pair of different keys $(x, y)$, any two of the $p(p-1)$ hash functions in $H_p$ hash them into different pairs $(r, s)$ of different remainders modulo $p$.

Therefore, any pair $(r, s)$ of different remainders modulo $p$ has equal probability $\frac{1}{p(p-1)}$.

The ratio of pairs $(r, s)$ of different remainders modulo $p$ such that $r \equiv s$ (mod $m$) is less than $\frac{1}{m}$.

Procedure for hashing phone numbers:

1. Define maximum length $L$ of a phone number
2. Convert phone numbers to integers from $0$ to $10^L - 1$
3. Choose prime number $p \gt 10^L$
4. Choose hash table size $m$
5. Choose random hash function from universal family $H_p$ (choose random $a \in [1, p-1]$ and $b \in [0, p-1]$)

### String Hashing

Denote by $\lvert S \rvert$ the length of string $S$.

A family of hash functions $P_p = \set{h_p^x(S) = \sum_{i=0}^{\lvert S \rvert - 1}{S[i]x^i \text{ mod } p}}$ with a fixed prime $p$ and all $1 \leq x \leq p-1$ is called polynomial.

Procedure for hashing e.g. names:

1. Convert each character $S[i]$ to an integer (ASCII encoding, Unicode, etc.)
2. Choose a big prime number $p$
3. Apply poly hash

```pseudocode
PolyHash(S, p, x):
  hash <- 0
  for i from |S|-1 down to 0:
    hash <- (hash*x + S[i]) mod p
  return hash
```

### Polynomial Hashing

For any two different strings $s_1$ and $s_2$ of length at most $L+1$, if you choose $h$ from $P_p$ at random (by selecting a random $x\in[1, p-1]$), the probability of collision $P[h(s_1) = h(s_2)]$ is at most $\frac{L}{p}$.

This is because the equation $a_0 + a_1x + a_2x^2 + \dots + a_Lx^L = 0$ (mod $p$) for prime $p$ has at most $L$ different solutions $x$.

For any two different strings $s_1$ and $s_2$ of length at most $L+1$ and cardinality $m$, the probability of collision $P[h_m(s_1) = h_m(s_2)]$ is at most $\frac{1}{m} + \frac{L}{p}$.

Therefore, if $p \gt mL$, for any two different strings $s_1$ and $s_2$ of length at most $L+1$ the probability of collision $P[h_m(s_1) = h_m(s_2)]$ is $O(\frac{1}{m})$.

Proof:

$$
\frac{1}{m} + \frac{L}{p} \lt \frac{1}{m} + \frac{L}{mL} = \frac{1}{m} + \frac{1}{m} = \frac{2}{m} = O(\frac{1}{m})
$$

**Running time:** Thus, for $p \gt mL$, we have $c = O(1 + \frac{n}{m}) = O(1 + \alpha)$ again.

Computing `PolyHash(S)` runs in $O(\lvert S \rvert)$.

If lengths of the names in the phone book are bounded by a constant $L$, computing $h(S)$ takes $O(L) = O(1)$ time.

Thus, **search and modification in a hash table run in** $O(1)$ **time on average!**

### Finding a Substring in a Text - Rabin-Karp Algorithm

- If $h(P) \neq h(S)$ then definitely $P \neq S$
- If $h(P) = h(S)$ call `AreEqual(P, S)` to check whether $P=S$ or not

Use polynomial hash family $P_p$ with prime $p$.

The idea is that if $P \neq S$, the probability $P[h(P) = h(S)]$ of collision (i.e. a **false alarm**) is at most $\frac{\lvert P \rvert}{p}$ for polynomial hashing.

On average, the total number of false alarms will be $\frac{(\lvert T \rvert - \lvert P \rvert + 1) \lvert P \rvert}{p}$.

This can be made small by choosing a very large prime $p \gg \lvert T \rvert \lvert P \rvert$.

### Blockchain

For some hash functions, e.g. MD5, it is extremely hard to find another string with exactly the same value.

It is possible to use hash functions to make short digests of arbitrary strings.

$$
H[i+1] = h(h(Text[i+1]) \circ H[i])
$$

Note how the hash of the current text is concatenated with the previous text's hash. This way, to forge any particular record in a diary, one would have to also forge all the records after it to fix the hash values.

An additional security measure is to add a number called **nonce**) in brackets to the end of each record in such a way that the hash column value always ends with three zeros (i.e. is divisible by 1000). The remainder of the resulting hash value modulo 1000 will be any number between 0 and 999 with approximately the same probability. And to come up with the right nonce, one has to try them all one by one. Therefore, it would take on average around 500 steps until she finds a nonce with remainder 0 mod 1000. Thus, there is a trade-off that can be controlled between the effort required to keep the diary and the effort needed to forge it.

To avoid sending each lender hashes of the whole diary to check just one transaction, we can separate it into blocks of transactions (corresponding to pages in a real physical diary). This represents the diary as a chain of blocks - hence the name.

*Blockchain is in essence just a diary which is very hard to forge. Typically, it is distributed and allows anybody to generate blocks which are verified and then added to the chain.*

#### Merkle Tree

To check that a transaction is recorded in a block, we saw that we need to send the whole chain of transactions inside the block and compute the whole chain of hashes. Thus, it requires $O(n)$ time for $n$ transactions in a block.

*A Merkle tree is a binary tree that makes it possible to reduce this time to* $O(\log n)$.

## Binary Search Trees

Motivation: Need a data structure for *local search*

**Search tree property:** X's key is larger than the key of any descendent of its left child, and smaller than the key of any descendent of its right child.

Optimally, we want a **(perfectly) balanced tree**, i.e. one where the left and right subtrees have approximately the same size.

### AVL Trees

Motivation: Want to maintain tree balance

**AVL property:** For all nodes $N$, $\lvert N.Left.Height - N.Right.Height \rvert \leq 1$

Question: Suppose we enforce the AVL property only for the root of the tree, but not for all the nodes. Can such a tree be unbalanced? Yes. Such a tree could have height $n/2$ where $n$ is the number of nodes: two chains of length $n/2$ having root as the only common node form such a tree.

If you can maintain the AVL property, you can perform all operations (incl. rebalancing operations themselves) in $O(\log(n))$ time.

#### Split and Merge

Another useful feature of binary search trees is the ability to recombine them in interesting ways:

- `Merge` combines two binary search trees into a single one.
- `Split` breaks one binary search tree into two.

`AVLMergeWithRoot` maintains balance and runs in $O(h_{max}) = O(\log(n))$.

Question: Can the `Insert` operation be implemented given only Split and Merge operations? Yes. First create a new tree with a single key - the key to be inserted. Then split the current tree by this key. Then merge the left splitted part with the new tree. Then merge the result with the right splitted part.

Question: Can the `Delete` operation be implemented given only Split and Merge operations? Yes. Suppose we are deleting key $x$. Split the key twice: one split such that all the keys $\lt x$ go to the left, and all the keys $\geq x$ go to the right. Then split the right part of the first split such that all the keys $\leq x$ go to the left and all the keys $gt x$ go to the right. Then merge the left part of the first split and the right part of the second split - thus leaving out the node with key $x$.

### Splay Trees

Idea: Want common nodes near root in order to make search for those faster (than $O(\log(n))$).

The `Splay` operation can be used to rebalance a search tree to this end, i.e. to bring each query node to the root.

The amortised cost of doing $O(D)$ work and then splaying a node of depth $D$ is $O(\log(n))$ where $n$ is the total number of nodes.

Consider a a node at depth $D$. Then

- $O(D)$ time to find $N$.
- Splay N.
- Amortised cost $O(\log(n))$.

You pay for the work of finding $N$ by splaying to rebalance the tree.

In summary, splay trees perform all operations simply in $O(\log(n))$ amortised time.

Question: What will happen if you forget to splay the last accessed vertex in the implementation of `Find` in case the key was not found in the splay tree?

The tree will still work but be [slow](https://www.cs.usfca.edu/~galles/visualization/SplayTree.html) on some sequences of operations.

Question: What will happen if you splay the node with the smallest key in a splay tree? The root of the new tree won't have a left child. The node with the smallest key will become the root after splaying, and it cannot have a left child because the key of the left child must be smaller than the key of its parent.

Question: What will happen if you select a node `N`, splay its predecessor `P` (the node with the largest key smaller than the key of `N`), then splay the node `N` itself? `N` will be the root, `P` will be the left child of the root, `P` won't have a right child.

After the first splay, `P` will become the root. After the second splay, `N` will become the root, and `P` will become its child, and it will be on the left, because its key is smaller. `P` won't have a right child, because a right child of `P` must have key bigger than the key of `P`, and also it must have key smaller than the key of `N` (because it is now in the left subtree of `N`), but it can't happen, because `P` is the predecessor of `N`, so there are no keys between the key of `P` and the key of `N`.
