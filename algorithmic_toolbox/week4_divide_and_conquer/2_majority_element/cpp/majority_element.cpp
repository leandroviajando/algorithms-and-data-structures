#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::vector;

int get_majority_element(vector<int>& a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];

  std::unordered_map<int, int> freq;
  for (int i = left; i < right; i++) freq[a[i]]++;

  auto most_common_element = max_element(freq.begin(), freq.end(), [](const auto& a, const auto& b) {
    return a.second < b.second;
  });

  return most_common_element->second > (right - left) / 2 ? most_common_element->first : -1;
}
