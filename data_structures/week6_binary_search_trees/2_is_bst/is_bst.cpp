#include <algorithm>
#include <iostream>
#include <vector>

namespace is_bst {
struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool is_bst(const std::vector<Node>& tree, int idx = 0, int min = -2147483648, int max = 2147483647) {
  if (tree.size() == 0) return true;
  if (idx == -1) return true;
  if (tree[idx].key < min || tree[idx].key >= max) return false;

  bool left_is_bst = is_bst(tree, tree[idx].left, min, tree[idx].key);
  bool right_is_bst = is_bst(tree, tree[idx].right, tree[idx].key, max);

  return left_is_bst && right_is_bst;
}
}  // namespace is_bst

int main() {
  int nodes;
  std::cin >> nodes;

  std::vector<is_bst::Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    std::cin >> key >> left >> right;
    tree.push_back(is_bst::Node(key, left, right));
  }
  std::cout << (is_bst::is_bst(tree) ? "CORRECT" : "INCORRECT") << std::endl;
  return 0;
}
