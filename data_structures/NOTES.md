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
