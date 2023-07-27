#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class TreeOrders {
  int n;
  std::vector<int> key;
  std::vector<int> left;
  std::vector<int> right;

 public:
  void read() {
    std::cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++)
      std::cin >> key[i] >> left[i] >> right[i];
  }

  std::vector<int> in_order() {
    std::vector<int> result;

    int current_id = 0;
    std::vector<int> stack;

    while (true) {
      if (current_id != -1) {
        stack.push_back(current_id);
        current_id = left[current_id];
      } else if (!stack.empty()) {
        current_id = stack.back();
        stack.pop_back();
        result.push_back(key[current_id]);
        current_id = right[current_id];
      } else
        break;
    }

    return result;
  }

  std::vector<int> pre_order() {
    std::vector<int> result;

    int current_id = 0;
    std::vector<int> stack;

    while (true) {
      if (current_id != -1) {
        result.push_back(key[current_id]);
        stack.push_back(current_id);
        current_id = left[current_id];
      } else if (!stack.empty()) {
        current_id = stack.back();
        stack.pop_back();
        current_id = right[current_id];
      } else
        break;
    }

    return result;
  }

  std::vector<int> post_order() {
    std::vector<int> result;

    std::vector<int> stack1 = {0};
    std::vector<int> stack2;

    while (!stack1.empty()) {
      int current_id = stack1.back();
      stack1.pop_back();
      stack2.push_back(current_id);

      if (left[current_id] != -1)
        stack1.push_back(left[current_id]);

      if (right[current_id] != -1)
        stack1.push_back(right[current_id]);
    }

    while (!stack2.empty()) {
      result.push_back(key[stack2.back()]);
      stack2.pop_back();
    }

    return result;
  }
};

void print(std::vector<int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0)
      std::cout << ' ';
    std::cout << a[i];
  }
  std::cout << std::endl;
}

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main(int argc, char **argv) {
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;  // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
    if (rl.rlim_cur < kStackSize) {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0)
        std::cerr << "setrlimit returned result = " << result << std::endl;
    }
  }
#endif

  return main_with_large_stack_space();
}
