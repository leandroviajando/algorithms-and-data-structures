#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

string bwt(const string& text) {
  string result = "";

  vector<string> matrix;
  for (int i = 0; i < text.size(); i++)
    matrix.push_back(text.substr(i, text.size() - i) + text.substr(0, i));

  std::sort(matrix.begin(), matrix.end());

  for (int i = 0; i < matrix.size(); i++)
    result += matrix[i][matrix[i].size() - 1];

  return result;
}

int main() {
  string text;
  std::cin >> text;
  std::cout << bwt(text) << std::endl;
  return 0;
}
