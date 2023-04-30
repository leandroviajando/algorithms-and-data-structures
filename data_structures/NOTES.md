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
