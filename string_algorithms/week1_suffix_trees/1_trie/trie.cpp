#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string>& patterns) {
  trie t(1);          // Start with a single root node
  int nodeCount = 1;  // Keep track of the number of nodes

  for (const string& pattern : patterns) {
    int currentNode = 0;  // Start at the root node

    for (char symbol : pattern) {
      if (t[currentNode].find(symbol) != t[currentNode].end())
        currentNode = t[currentNode][symbol];  // If the edge with 'symbol' already exists, follow it to the next node
      else {                                   // Else create a new node and add the edge
        t[currentNode][symbol] = nodeCount;
        t.push_back(edges());
        currentNode = nodeCount;
        nodeCount++;
      }
    }
  }

  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i)
    for (const auto& j : t[i])
      std::cout << i << "->" << j.second << ":" << j.first << std::endl;

  return 0;
}
