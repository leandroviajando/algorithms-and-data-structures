# [Grokking Coding Interview Patterns in C++](https://www.educative.io/courses/grokking-coding-interview-patterns-cpp/)

## Two Pointers

- Useful to keep track of values of two different indices in a single iteration.
- Essentially, an application of the prune-and-search-strategy, i.e. at every step, eliminating a set of possible solutions.

Requirements:

- The input can be traversed in a linear fashion.
- The problem does not require an exhaustive search of the solution space (in which case, eliminating one solution would not eliminate any others).

Examples:

- Palindrome
- Array reversal
- Memory management: The memory pool is initialized with two pointers: the start pointer, pointing to the beginning of the available memory block, and the end pointer, indicating the end of the block. When a process or data structure requests memory allocation, the start pointer is moved forward, designating a new memory block for allocation. Conversely, when memory is released (deallocated), the start pointer is shifted backward, marking the deallocated memory as available for future allocations.
- Product suggestions: While shopping online, when customers view their cart and the current total doesn’t qualify for free shipping, we want to show them pairs of products that can be bought together to make the total amount equal to the amount required to be eligible for free delivery. Two pointers can be used to suggest the pairs that add up to the required cost for free shipping.

## Fast and Slow Pointers

## Sliding Window

## Merge Intervals

## In-Place Reversal of a Linked List

## Two Heaps

## K-Way Merge

## Top K Elements

## Modified Binary Search

## Subsets

## Greedy Techniques

## Backtracking

## Dynamic Programming

## Cyclic Sort

## Topological Sort

## Matrices

## Stacks

## Graphs

## DFS

## BFS

## Tries

## Hashmaps

## Knowing What to Track

## Union Find

## Custom Data Structures

## Bitwise Manipulation
