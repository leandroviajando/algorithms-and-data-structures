#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

const vector<char> LETTERS = {'$', 'A', 'C', 'G', 'T'};

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position
//       of this character in the sorted array of
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void preprocessBWT(const string& bwt,
                   map<char, int>& starts,
                   map<char, vector<int>>& occ_count_before) {
  std::unordered_map<char, int> freq;
  for (char c : LETTERS)
    freq[c] = 0;

  for (char c : bwt)
    freq[c]++;

  starts['$'] = 0;
  for (int i = 1; i < LETTERS.size(); i++)
    starts[LETTERS[i]] = starts[LETTERS[i - 1]] + freq[LETTERS[i - 1]];

  for (char letter : LETTERS)
    occ_count_before[letter] = vector<int>(bwt.size() + 1, 0);

  for (int i = 0; i < bwt.size(); i++) {
    std::unordered_map<char, int> tmp_dict;
    tmp_dict[bwt[i]] = 1;
    for (char letter : LETTERS)
      occ_count_before[letter][i + 1] = occ_count_before[letter][i] + tmp_dict[letter];
  }
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int countOccurrences(const string& bwt,
                     string& pattern,
                     map<char, int>& starts,
                     map<char, vector<int>>& occ_count_before) {
  int top = 0;
  int bottom = bwt.size() - 1;

  while (!pattern.empty()) {
    char symbol = pattern.back();
    pattern.pop_back();

    top = starts[symbol] + occ_count_before[symbol][top];
    bottom = starts[symbol] + occ_count_before[symbol][bottom + 1] - 1;

    if (top > bottom)
      return 0;
  }

  return bottom - top + 1;
}

int main() {
  string bwt;
  cin >> bwt;

  int pattern_count;
  cin >> pattern_count;

  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function preprocessBWT
  map<char, int> starts;

  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function preprocessBWT
  map<char, vector<int>> occ_count_before;

  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  preprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = countOccurrences(bwt, pattern, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
