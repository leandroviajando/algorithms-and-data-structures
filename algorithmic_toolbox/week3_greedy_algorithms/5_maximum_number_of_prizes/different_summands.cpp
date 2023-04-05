#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;

  for (int i = 1; i <= n; i++) {
    if (n - i > i) {
      summands.push_back(i);
      n -= i;
    } else {
      summands.push_back(n);
      break;
    }
  }

  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << std::endl;
  for (size_t i = 0; i < summands.size(); ++i)
    std::cout << summands[i] << ' ';
}
