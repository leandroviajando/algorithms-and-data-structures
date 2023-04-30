#include <iostream>
#include <vector>

class HeapBuilder {
 private:
  std::vector<int> data_;
  std::vector<std::pair<int, int>> swaps_;

  void WriteResponse() const {
    std::cout << swaps_.size() << std::endl;
    for (int i = 0; i < swaps_.size(); ++i)
      std::cout << swaps_[i].first << " " << swaps_[i].second << std::endl;
  }

  void ReadData() {
    int n;
    std::cin >> n;
    data_.resize(n);
    for (int i = 0; i < n; ++i)
      std::cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.

    // TODO: replace by a more efficient implementation
    // for (int i = 0; i < data_.size(); ++i)
    //   for (int j = i + 1; j < data_.size(); ++j)
    //     if (data_[i] > data_[j]) {
    //       std::swap(data_[i], data_[j]);
    //       swaps_.push_back(std::make_pair(i, j));
    //     }

    // Start from the last non-leaf node and perform SiftDown for each node
    for (int i = data_.size() / 2; i >= 0; --i)
      SiftDown(i);
  }

  void SiftDown(int i) {
    int min_index = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    if (left_child < data_.size() && data_[left_child] < data_[min_index])
      min_index = left_child;

    if (right_child < data_.size() && data_[right_child] < data_[min_index])
      min_index = right_child;

    if (i != min_index) {
      std::swap(data_[i], data_[min_index]);
      swaps_.push_back(std::make_pair(i, min_index));
      SiftDown(min_index);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
