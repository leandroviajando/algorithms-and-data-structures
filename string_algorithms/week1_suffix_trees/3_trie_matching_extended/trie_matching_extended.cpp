#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace trie_matching_extended {
int const Letters = 4;
int const NA = -1;

struct Node {
  int next[Letters];
  bool patternEnd;

  Node() {
    fill(next, next + Letters, NA);
    patternEnd = false;
  }

  bool isLeaf() const {
    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
  }
};

int letterToIndex(char letter) {
  switch (letter) {
    case 'A':
      return 0;
    case 'C':
      return 1;
    case 'G':
      return 2;
    case 'T':
      return 3;
    default:
      assert(false);
      return -1;
  }
}

void buildTrie(const vector<string>& patterns, vector<Node>& trie) {
  trie.push_back(Node());  // Initialize the root node

  for (const string& pattern : patterns) {
    int currentNode = 0;  // Start at the root node

    for (char symbol : pattern) {
      int index = letterToIndex(symbol);

      if (trie[currentNode].next[index] == NA) {
        trie.push_back(Node());
        trie[currentNode].next[index] = trie.size() - 1;  // Update the edge
      }

      currentNode = trie[currentNode].next[index];  // Move to the next node
    }

    trie[currentNode].patternEnd = true;  // Mark the end of this pattern
  }
}

vector<int> solve(const string& text, int n, const vector<string>& patterns) {
  vector<int> result;
  vector<Node> trie;
  buildTrie(patterns, trie);

  for (int i = 0; i < text.size(); ++i) {
    int currentNode = 0;
    int j = i;

    while (true) {
      if (trie[currentNode].isLeaf()) {
        // If we reach a leaf node in the trie, it means we found a pattern
        result.push_back(i);
        break;
      }

      if (j >= text.size()) {
        // If we run out of characters in the text, stop searching
        break;
      }

      int index = letterToIndex(text[j]);
      if (trie[currentNode].next[index] != NA) {
        // Follow the edge if it exists
        currentNode = trie[currentNode].next[index];
        j++;

        if (trie[currentNode].patternEnd) {
          // If it's the end of a pattern, add its starting position
          result.push_back(i);
          break;
        }
      } else {
        // If the edge doesn't exist, stop searching
        break;
      }
    }
  }

  return result;
}
}  // namespace trie_matching_extended

int main(void) {
  string t;
  cin >> t;

  int n;
  cin >> n;

  vector<string> patterns(n);
  for (int i = 0; i < n; i++)
    cin >> patterns[i];

  vector<int> ans;
  ans = trie_matching_extended::solve(t, n, patterns);

  for (int i = 0; i < (int)ans.size(); i++) {
    cout << ans[i];
    if (i + 1 < (int)ans.size())
      cout << " ";
    else
      cout << endl;
  }

  return 0;
}
