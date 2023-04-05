#include <algorithm>
#include <iostream>
#include <vector>

struct Item {
  int weight;
  int value;
  double unit_value;
};

bool compare(const Item& a, const Item& b) {
  return a.unit_value > b.unit_value;
}

double get_optimal_value(int capacity, const std::vector<int> weights, const std::vector<int> values) {
  int weight = 0;
  double value = 0.0;

  std::vector<Item> items;
  for (size_t i = 0; i < weights.size(); i++)
    items.push_back({weights[i], values[i], (double)values[i] / weights[i]});

  std::sort(items.begin(), items.end(), compare);

  for (auto& item : items) {
    if (weight >= capacity) break;

    int units = std::min(item.weight, capacity - weight);
    weight += units;
    value += units * item.unit_value;
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  std::vector<int> values(n);
  std::vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
