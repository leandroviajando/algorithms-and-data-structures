#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

vector<int> compute_prefix_function(const string& pattern) {
  vector<int> s(pattern.size());
  s[0] = 0;
  int border = 0;

  for (int i = 1; i < pattern.size(); ++i) {
    while (border > 0 && pattern[i] != pattern[border])
      border = s[border - 1];

    if (pattern[i] == pattern[border])
      border++;
    else
      border = 0;

    s[i] = border;
  }

  return s;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  string S = pattern + '$' + text;
  vector<int> s = compute_prefix_function(S);

  vector<int> result;
  for (int i = pattern.size() + 1; i < S.size(); ++i)
    if (s[i] == pattern.size())
      result.push_back(i - 2 * pattern.size());

  return result;
}

int main() {
  string pattern, text;
  std::cin >> pattern;
  std::cin >> text;

  vector<int> result = find_pattern(pattern, text);

  for (int i = 0; i < result.size(); ++i)
    std::cout << result[i] << " ";
  std::cout << std::endl;
  return 0;
}
