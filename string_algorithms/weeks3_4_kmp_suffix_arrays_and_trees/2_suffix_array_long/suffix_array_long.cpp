#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::make_pair;
using std::pair;
using std::string;
using std::vector;

const int ALPHABET_SIZE = 256;

vector<int> sort_characters(const string& text) {
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

vector<int> compute_char_classes(const string& text, const vector<int>& order) {
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

vector<int> sort_doubled(const string& text, int L, const vector<int>& order, const vector<int>& classes) {
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

vector<int> update_classes(const vector<int>& new_order, const vector<int>& classes, int L) {
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
vector<int> build_suffix_array(const string& text) {
  vector<int> order = sort_characters(text);
  vector<int> classes = compute_char_classes(text, order);
  int L = 1;
  while (L < text.size()) {
    order = sort_doubled(text, L, order, classes);
    classes = update_classes(order, classes, L);
    L *= 2;
  }
  return order;
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
