#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class StackWithMax {
  std::vector<int> stack;

 public:
  void Push(int value) { stack.push_back(value); }

  void Pop() {
    assert(stack.size());
    stack.pop_back();
  }

  int Max() const {
    assert(stack.size());
    return *std::max_element(stack.begin(), stack.end());
  }
};

int main() {
  int num_queries = 0;
  std::cin >> num_queries;

  std::string query;
  std::string value;

  StackWithMax stack;

  for (int i = 0; i < num_queries; ++i) {
    std::cin >> query;
    if (query == "push") {
      std::cin >> value;
      stack.Push(std::stoi(value));
    } else if (query == "pop")
      stack.Pop();
    else if (query == "max")
      std::cout << stack.Max() << std::endl;
    else
      assert(0);
  }
  return 0;
}
