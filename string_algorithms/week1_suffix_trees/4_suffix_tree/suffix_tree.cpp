#include <deque>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>

using namespace std;

namespace suffix_tree {
struct Node {
  optional<string> label;
  map<char, Node> outgoing_edges;

  Node(const string& str = "") : label(str) {}
};

void AddSuffix(Node& root, const string& suffix) {
  Node* currentNode = &root;

  for (char symbol : suffix) {
    if (currentNode->outgoing_edges.find(symbol) == currentNode->outgoing_edges.end())
      currentNode->outgoing_edges[symbol] = Node();

    currentNode = &currentNode->outgoing_edges[symbol];
  }
}

void TraverseTree(const Node& root, vector<string>& result) {
  deque<const Node*> dq;
  dq.push_back(&root);

  while (!dq.empty()) {
    const Node* u = dq.front();
    dq.pop_front();

    if (u->label.has_value())
      result.push_back(u->label.value());

    for (const auto& pair : u->outgoing_edges)
      dq.push_back(&(pair.second));
  }
}

void ComputeSuffixTreeEdges(const string& s, vector<string>& result) {
  Node root;
  root.label = nullopt;
  root.outgoing_edges[s[0]] = Node();
  root.outgoing_edges[s[0]].label = s;

  for (int i = 1; i < s.length(); ++i) {
    Node* cur = &root;
    int j = i;
    while (j < s.length()) {
      if (cur->outgoing_edges.find(s[j]) != cur->outgoing_edges.end()) {
        Node& child = cur->outgoing_edges[s[j]];
        string label = child.label.value_or("");
        int k = j + 1;
        while (k - j < label.length() && s[k] == label[k - j])
          k += 1;

        if (k - j == label.length()) {
          cur = &child;
          j = k;
        } else {
          char cExist = label[k - j];
          char cNew = s[k];
          Node mid;
          mid.label = label.substr(0, k - j);
          mid.outgoing_edges[cNew] = Node(s.substr(k));
          child.label = label.substr(k - j);
          mid.outgoing_edges[cExist] = child;
          cur->outgoing_edges[s[j]] = mid;
        }
      } else
        cur->outgoing_edges[s[j]] = Node(s.substr(j));
    }
  }

  TraverseTree(root, result);
}
}  // namespace suffix_tree

int main() {
  string text;
  cin >> text;

  vector<string> edges;
  suffix_tree::ComputeSuffixTreeEdges(text, edges);

  for (const string& edge : edges)
    cout << edge << endl;

  return 0;
}
