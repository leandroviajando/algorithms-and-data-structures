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

## Knuth-Morris-Pratt Algorithm

The Knuth-Morris-Pratt Algorithm is a linear-time exact pattern matching algorithm.

### Exact Pattern Matching

Input: Strings `Text` and `Pattern`

Output: All such positions in `Text` where `Pattern` appears as a substring

A naive brute-force algorithm, sliding the pattern down the text, in the worst case runs in $\Theta( \lvert T \rvert \lvert P \rvert )$.

### Skipping Positions

A **border** of a string $S$ is a prefix of $S$ which is equal to a suffix of $S$, but not equal to the whole of $S$.

Shifting patterns:

1. Find longest common prefix $u$
2. Find $w$ - the longest border of $u$
3. Move $P$ such that the prefix $w$ in $P$ aligns with suffix $w$ of $u$ in $T$

Thus, we can skip some of the comparisons.

But we shouldn't miss any of the pattern occurrences in the text. Is it *safe* to shift the pattern this way?

### Safe Shift

Denote by $S_k$ the suffix of string $S$ starting at position $k$.

Let $u$ bet the longest common prefix of $P$ and $T_k$. Let $w$ be the longest border of $u$. Then there are no occurrences of $P$ in $T$ starting between positions $k$ and $(k + \lvert u \rvert - \lvert w \rvert )$ - the start of suffix $w$ in the prefix $u$ of $T_k$.

Thus, it is possible to avoid many of the comparisons of the Brute Force algorithm.

### Prefix Function

How do we determine the best pattern shifts?

A **prefix function** of a string $P$ is a function $s(i)$ that for each $i$ returns the length of the longest border of the prefix $P[0..i]$.

$P[0..i]$ has a border of length $s(i + 1) - 1$.

As a corollary, $s(i + 1) \leq s(i) + 1$.

If $s(i) \gt 0$, then all borders of $P[0..i]$ but for the longest one are also borders of $P[0..s(i) - 1]$.

As a corollary, all borders of $P[0..i]$ can be enumerated by taking the longest border $b_1$ of $P[0..i]$, then the longest border $b_2$ of $b_1$, then the longest border $b_3$ of $b_2$, and so on.

### Computing the Prefix Function

| $P$ | a | b | a | b | a | b | c | a | a | b |
| --- | - | - | - | - | - | - | - | - | - | - |
| $s$ | 0 | 0 | 1 | 2 | 3 | 4 | 0 | 1 | 1 | 2 |

```c++
vector<int> compute_prefix_function(const string& pattern) {
    vector<int> s(pattern.size());
    s[0] = 0;

    int border = 0;
    for (int i = 1; i < pattern.size(); ++i) {
        while (border > 0 && pattern[i] != pattern[border])
            border = s[border - 1];

        if (pattern[i] == pattern[border])
            border++;
        else
            border = 0;

        s[i] = border;
    }
    return s;
}
```

The running time of this algorithm is **linear**, $O( \lvert P \rvert )$.

### The Knuth-Morris-Pratt Algorithm

$P$: `abra`
$T$: `abracadabra`

| $S$ | a | b | r | a | $ | a | b | r | a | c | a | d | a | b | r | a |
| --- | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| $s$ | 0 | 0 | 0 | 1 | 0 | 1 | 2 | 3 | 4 | 0 | 1 | 0 | 1 | 2 | 3 | 4 |

```c++
vector<int> kmp(const strin& pattern, const string& text) {
    string S = pattern + '$' + text;
    vector<int> s = compute_prefix_function(S);

    vector<int> result;
    for (int i = pattern.size() + 1; i < S.size(); ++i)
        if (s[i] == pattern.size())
            result.push_back(i - 2 * pattern.size());

    return result;
}
```

The running time of the Knuth-Morris-Pratt algorithm is **linear**, $O( \lvert P \rvert + \lvert T \rvert )$.

## Constructing Suffix Arrays

Input: String $S$

Output: All suffixes of $S$ in lexicographic order (e.g. `"ab" < "bc"`, `"abc" < "abd"`, `"abc" < "abcd"`)

Memory:

- The total length of all suffixes is $1 + 2 + \dots + \lvert S \rvert = \Theta( \lvert S \rvert^2)$
- Storing them all is too much memory
- Therefore, store the order of suffixes $O( \lvert S \rvert )$

For example, given $S = ababaa\$$, suffixes are numbered by their starting positions: $ababaa\$$ is 0, $abaa\$$ is 2, etc. Thus, the suffix array is $[6, 5, 4, 2, 0, 3, 1]$.

### General Construction Strategy

Adding a character $ smaller than all other characters to the end of a string $S$ results in sorting cyclic shifts of $S$ and suffixes of $S$ being equivalent.

Substrings of cyclic string $S$ are called partial cyclic shifts of $S$.

Strategy:

1. Start with sorting single characters of $S$.
2. Cyclic shifts of length $L = 1$ sorted.
3. While $L \leq \lvert S \rvert$, sort shifts of length $2L$.
4. If $L \geq \lvert S \rvert$, cyclic shifts of length $L$ sort the same way as cyclic shifts of length $S$.

```c++
vector<int> build_suffix_array(const string& text) {
    vector<int> order = sort_characters(text);
    vector<int> classes = compute_char_classes(text, order);
    int L = 1;
    while (L < text.size()) {
        order = sort_doubled(text, L, order, classes);
        classes = update_classes(order, classes, L);
        L *= 2;
    }
    return order;
}
```

### Initialisation

```c++
const int ALPHABET_SIZE = 256;

vector<int> sort_characters(const string& text) {
    vector<int> order(text.size());
    vector<int> count (ALPHABET_SIZE, 0);
    for (int i = 0; i < text.size(); ++i)
        count[text[i]]++;
    for (int j = 1; j < ALPHABET_SIZE; ++j)
        count[j] += count[j - 1];
    for (int i = text.size() - 1; i >= 0; --i) {
        int c = text[i];
        count[c]--;
        order[count[c]] = i;
    }
    return order;
}
```

The running time of this algorithm is $O( \lvert S \rvert + \lvert \Sigma \rvert )$.

```c++
vector<int> compute_char_classes(const string& text, const vector<int>& order) {
    vector<int> classes(text.size());
    classes[order[0]] = 0;
    for (int i = 1; i < text.size(); ++i) {
        if (text[order[i]] != text[order[i - 1]])
            classes[order[i]] = classes[order[i - 1]] + 1;
        else
            classes[order[i]] = classes[order[i - 1]];
    }
    return classes;
}
```

The running time of this algorithm is $O( \lvert S \rvert )$.

### Counting Sort

A simple, but crucial observation: the Counting Sort algorithm is stable. It means that it keeps the order of equal elements. Of course, it doesn't matter for the sorting algorithm itself in what order to put equal elements: they can go in any order in the sorted array. But for some algorithms that use sorting it is important, as we will see in the following lecture. If you sort an array which has equal elements using Counting Sort, and one of the two equal elements was before another one initially in the array, it will still go first after sorting. Also see this [answer](http://programmers.stackexchange.com/questions/247440/what-does-it-mean-for-a-sorting-algorithm-to-be-stable) for an example of difference between stable sorting and a non-stable sorting algorithms.

### Sort Doubled Cyclic Shifts

```c++
vector<int> sort_doubled(const string& text, int L, const vector<int>& order, const vector<int>& classes) {
    vector<int> count(text.size(), 0);
    vector<int> new_order(text.size());
    for (int i = 0; i < text.size(); ++i)
        count[classes[i]]++;
    for (int j = 1; j < text.size(); ++j)
        count[j] += count[j - 1];
    for (int i = text.size() - 1; i >= 0; --i) {
        int start = (order[i] - L + text.size()) % text.size();
        int cl = classes[start];
        count[cl]--;
        new_order[count[cl]] = start;
    }
    return new_order;
}
```

### Updating Classes

```c++
vector<int> update_classes(const vector<int>& new_order, const vector<int>& classes, int L) {
    int n = new_order.size();
    vector<int> new_classes(n);
    new_classes[new_order[0]] = 0;
    for (int i = 1; i < n; ++i) {
        int cur = new_order[i];
        int prev = new_order[i - 1];
        int mid = (cur + L) % n;
        int mid_prev = (prev + L) % n;
        if (classes[cur] != classes[prev] || classes[mid] != classes[mid_prev])
            new_classes[cur] = new_classes[prev] + 1;
        else
            new_classes[cur] = new_classes[prev];
    }
    return new_classes;
}
```

## From Suffix Arrays to Suffix Trees

### LCP Arrays

### Constructing Suffix Trees
