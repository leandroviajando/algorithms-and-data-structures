# Algorithms on Strings

## Tries and Suffix Trees

### From Genome Sequencing to Pattern Matching

Where does a read match the reference genome approximately?

The Approximate Pattern Matching Problem:

Input: A string `Pattern`, a string `Text`, and an integer `d`.

Output: All positions in `Text` where `Pattern` appears as a substring with at most `d` mismatches.

### Brute Force Approach to Pattern Matching

$O( \lvert Text \rvert \cdot \lvert Pattern(s) \rvert )$

This is fast for a single pattern, but slow as the number of patterns increases.

### Herding Patterns into a Trie

`Trie(Patterns)` is a rooted tree storing all patterns from `Patterns` in a way that minimizes the number of edges.

Then `TrieMatching(Text, Patterns)` drives the `Trie(Patterns)` along the `Text`. A pattern matches `Text` each time you reach a leaf!

This is faster than brute force: $O( \lvert Text \rvert + \lvert LongestPattern \rvert )$

### Herding Text into a Suffix Trie

New idea:

- Generate all suffixes of `Text`.
- Form a trie out of these suffixes (a suffix trie).
- For each `Pattern`, check if it can be spelled out from the root downward in the `SuffixTrie`.
- To find the positions of the matches, add that information to the leaves of the `SuffixTrie`.
- Once we find a match, we "walk down" to the leaf (or leaves) in order to find the starting position of the match.

The **memory** footprint of a suffix trie is $O( \lvert Text \rvert \cdot \frac{\lvert Text \rvert - 1}{2} ) = O( \lvert Text \rvert^2 )$. For a human genome, for example, this is too much.

### From Suffix Tries to Suffix Trees

Compress the suffix trie by merging nodes with a single outgoing edge.

Storing only the edge labels is sufficient to reconstruct the trie.

Then, since each suffix adds one leaf and at most one internal vertex to the suffix tree: $\#vertices < 2 \lvert Text \rvert$; and therefore, the **memory** footprint is simply the length of the text $O( \lvert Text \rvert )$. The **running time** of doing pattern matching with a suffix tree is $O( \lvert Text \rvert + \lvert Patterns \rvert )$.

### Quiz

1. What is the tightest estimate you can prove on the memory consumption of a trie built off $n$ non-empty patterns $p_1, p_2, \dots, p_n$ if all the patterns' lengths are bounded from above by $L$, and the sum of lengths of all patterns is no more than $S$?

Even if all patterns start with different characters, and so each pattern creates a whole separate branch of the tree, still the sum of lengths of those branches is no more than the total number of characters in all the patterns - which is $S$.

You will also need some space for the root vertex of the trie, but this is just $O(1)$.

You also need to store the links from the nodes of the trie to their children, but the total number of such links is also $O(S)$, and if you store them using lists of children in each node, it will take $O(S)$ memory (if you store an array of potential children of size $A$, the size of the alphabet, in each node, you'll need more memory - $O(SA)$).

However, if you use regular linked lists, searching in such a trie could become too slow. Instead, you can store a hash table in each node, mapping from characters to the corresponding children.

We also need an additional $O(n)$ memory to store $n$ patterns, but if all $n$ patterns are non-empty, then $S \geq n$, so $O(S + n) = O(S)$.

2. What is the time complexity of searching all occurrences of $n$ patterns $p_1, p_2, \dots, p_n$ in text $T$ of length $\lvert T \rvert$ if all patterns have length at most $L$ and the sum of their lengths is at most $S$?

For each of the $\lvert T \rvert$ starting positions in the text $T$, in the worst case you would need to traverse the trie from its root to the deepest node, and any such path has length at most $L$: $O(\lvert T \rvert L)$.

3. What is the smallest possible number of nodes in a trie built off $n$ patterns $p_1, p_2, \dots, p_n$ if all the patterns have the same length $L \gt 0$?

If all the patterns are the same, you will need exactly $L+1$ nodes: the root node and $L$ more nodes to store each character of the first pattern. All the other patterns will use the same nodes.

4. If you take all the suffixes of a string $S$ of length $L$ and build a regular trie off those suffixes as patterns, what is the maximum possible number of nodes in such a trie?

If all the characters in $S$ are different, all the suffixes will start with different characters, so each of them will require a whole separate branch in the trie. The longest suffix will generate a branch of length $L$, the next one will generate a branch of length $L-1$, and so on, down to length $1$ for the shortest suffix. The total number of nodes will be $1 + L + (L-1) + \dots + 1 = \frac{L(L+1)}{2} + 1 = O(L^2)$.

5. What is the smallest possible number of nodes in a suffix tree of string $S$ with length $L$?

If the string $S$ is $aaa \dots aaa$, then all the suffixes of this string are also of the form $aaa \dots aaa$, so they will all fit into the single branch of the suffix tree. This branch will contain the root node and $L$ more nodes for the longest suffix of the string $S$.

## Burrows-Wheeler Transform and Suffix Arrays

### Burrows-Wheeler Transform

In 1994, Michael Burrows and David Wheeler invented an ingenious algorithm for **text compression** that is now known as Burrows-Wheeler Transform.

The Burrows–Wheeler transform of a string `Text` permutes the symbols of `Text` so that it becomes well compressible. Moreover, the transformation is **reversible**: one can recover the initial string `Text` from its Burrows–Wheeler transform. However, data compression is not its only application: it is also used for solving the multiple **pattern matching** problem and the **sequence alignment** problem.

`BWT(Text)` is defined as follows:

1. Form all possible cyclic rotations of `Text`; a cyclic rotation is
defined by chopping off a suffix from the end of `Text` and appending this suffix to the beginning of `Text`.
2. Then, order all the cyclic rotations of `Text` lexicographically to form a `|Text|×|Text|` matrix of symbols denoted by `M(Text)`. `BWT(Text)` is the last column of `M(Text)`

#### Pattern Matching with the Burrows-Wheeler Transform

Pattern matching with Suffix Trees runs in $O( \lvert Text \rvert + \lvert Patterns \rvert )$ time, and requires $20 \cdot \lvert Text \rvert$ memory.

Can we use the Burrows-Wheeler Transform to design a more memory-efficient algorithm for pattern matching?

Not only the Burrows–Wheeler transform makes the input string Text well compressible, it also allows one to solve the pattern matching problem using the compressed strings instead of the initial string! This is another beautiful property of the Burrows–Wheeler transform which allows us to avoid decompressing the string, and thus to save lots of memory, while still solving the problem at hand.

### Suffix Arrays

A suffix array is a sorted array of all suffixes of a string.

It can be constructed from a suffix tree with a depth-first traversal of the tree in $O( \lvert Text \rvert )$ linear time and $O( \lvert Text \rvert )$ memory.

#### Pattern Matching with Suffix Arrays

### Approximate Pattern Matching and Mutations of the Genome

*Multiple* Approximate Pattern Matching Problem:

Input: A *set* of strings `Patterns`, a string `Text`, and an integer `d`.

Output: All positions in `Text` where one of the strings in `Patterns` appears as a substring with at most `d` mismatches.
