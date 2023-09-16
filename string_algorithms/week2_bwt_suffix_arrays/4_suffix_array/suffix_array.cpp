#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> build_suffix_array(const string& text) {
  vector<pair<string, int>> suffixes;
  for (int i = 0; i < text.size(); ++i)
    suffixes.push_back(make_pair(text.substr(i), i));

  std::sort(suffixes.begin(), suffixes.end());

  vector<int> result;
  for (int i = 0; i < suffixes.size(); ++i)
    result.push_back(suffixes[i].second);
  return result;
}

int main() {
  string text;
  std::cin >> text;

  vector<int> suffix_array = build_suffix_array(text);

  for (int i = 0; i < suffix_array.size(); ++i)
    std::cout << suffix_array[i] << ' ';
  std::cout << std::endl;
  return 0;
}
