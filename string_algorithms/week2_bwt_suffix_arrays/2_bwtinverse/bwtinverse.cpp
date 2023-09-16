#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

const vector<char> LETTERS = {'$', 'A', 'C', 'G', 'T'};

vector<int> map_last_col_to_first_col(string bwt) {
  unordered_map<char, int> counts;
  for (char c : LETTERS)
    counts[c] = 0;
  for (char c : bwt)
    counts[c]++;

  int total_count = -1;
  unordered_map<char, int> position;
  for (char letter : LETTERS) {
    total_count += counts[letter];
    position[letter] = total_count;
  }

  vector<int> array(bwt.size(), 0);
  for (int i = bwt.size() - 1; i >= 0; i--) {
    array[i] = position[bwt[i]];
    position[bwt[i]]--;
  }

  return array;
}

string bwtinverse(string bwt) {
  vector<int> last_to_first = map_last_col_to_first_col(bwt);

  string result(bwt.size(), '$');
  int pos = 0;
  for (int i = 1; i < bwt.size(); i++) {
    result[bwt.size() - i - 1] = bwt[pos];
    pos = last_to_first[pos];
  }

  return result;
}

int main() {
  string bwt;
  std::cin >> bwt;
  std::cout << bwtinverse(bwt) << std::endl;
  return 0;
}
