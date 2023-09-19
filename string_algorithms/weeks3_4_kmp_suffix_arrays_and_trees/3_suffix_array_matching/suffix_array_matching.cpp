#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::make_pair;
using std::pair;
using std::string;
using std::vector;

const int ALPHABET_SIZE = 256;

vector<int> sortCharacters(const string& text) {
  vector<int> order(text.size());
  vector<int> count(ALPHABET_SIZE, 0);
  for (int i = 0; i < text.size(); ++i)
    count[text[i]]++;
  for (int j = 1; j < ALPHABET_SIZE; ++j)
    count[j] += count[j - 1];
  for (int i = text.size() - 1; i >= 0; --i) {
    int c = text[i];
    count[c]--;
    order[count[c]] = i;
  }
  return order;
}

vector<int> computeCharClasses(const string& text, const vector<int>& order) {
  vector<int> classes(text.size());
  classes[order[0]] = 0;
  for (int i = 1; i < text.size(); ++i) {
    if (text[order[i]] != text[order[i - 1]])
      classes[order[i]] = classes[order[i - 1]] + 1;
    else
      classes[order[i]] = classes[order[i - 1]];
  }
  return classes;
}

vector<int> sortDoubled(const string& text, int L, const vector<int>& order, const vector<int>& classes) {
  vector<int> count(text.size(), 0);
  vector<int> new_order(text.size());
  for (int i = 0; i < text.size(); ++i)
    count[classes[i]]++;
  for (int j = 1; j < text.size(); ++j)
    count[j] += count[j - 1];
  for (int i = text.size() - 1; i >= 0; --i) {
    int start = (order[i] - L + text.size()) % text.size();
    int cl = classes[start];
    count[cl]--;
    new_order[count[cl]] = start;
  }
  return new_order;
}

vector<int> updateClasses(const vector<int>& new_order, const vector<int>& classes, int L) {
  int n = new_order.size();
  vector<int> new_classes(n);
  new_classes[new_order[0]] = 0;
  for (int i = 1; i < n; ++i) {
    int cur = new_order[i];
    int prev = new_order[i - 1];
    int mid = (cur + L) % n;
    int mid_prev = (prev + L) % n;
    if (classes[cur] != classes[prev] || classes[mid] != classes[mid_prev])
      new_classes[cur] = new_classes[prev] + 1;
    else
      new_classes[cur] = new_classes[prev];
  }
  return new_classes;
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  vector<int> order = sortCharacters(text);
  vector<int> classes = computeCharClasses(text, order);
  int L = 1;
  while (L < text.size()) {
    order = sortDoubled(text, L, order, classes);
    classes = updateClasses(order, classes, L);
    L *= 2;
  }
  return order;
}

vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
  vector<int> result;
  int min_index = 0;
  int max_index = text.size();
  while (min_index < max_index) {
    int mid_index = (min_index + max_index) / 2;
    int suffix_index = suffix_array[mid_index];
    string suffix = text.substr(suffix_index, pattern.size());
    if (pattern > suffix)
      min_index = mid_index + 1;
    else
      max_index = mid_index;
  }
  int start = min_index;
  max_index = text.size();
  while (min_index < max_index) {
    int mid_index = (min_index + max_index) / 2;
    int suffix_index = suffix_array[mid_index];
    string suffix = text.substr(suffix_index, pattern.size());
    if (pattern < suffix)
      max_index = mid_index;
    else
      min_index = mid_index + 1;
  }
  int end = max_index;
  for (int i = start; i < end; ++i)
    result.push_back(suffix_array[i]);
  return result;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j)
      occurs[occurrences[j]] = true;
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i])
      printf("%d ", i);
  }
  printf("\n");
  return 0;
}
