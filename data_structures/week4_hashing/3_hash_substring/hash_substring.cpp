#include <iostream>
#include <string>
#include <vector>

class RabinKarp {
  std::string _pattern;
  std::string _text;

  int _window;
  int _scan_bound;
  std::vector<int> _checksums;

 public:
  RabinKarp(const std::string& pattern, const std::string& text)
      : _pattern(pattern), _text(text), _window(pattern.length()), _scan_bound(text.length() - pattern.length() + 1), _checksums() {}

  int checksum(const std::string& s) {
    int sum = 0;

    for (char c : s)
      sum += static_cast<int>(c);

    return sum;
  }

  void precompute_hashes() {
    _checksums.push_back(checksum(_text.substr(0, _window)));

    for (int i = 1; i < _scan_bound; ++i) {
      int old_hash = _checksums[i - 1];
      int left_l_hash = static_cast<int>(_text[i - 1]);
      int right_l_hash = static_cast<int>(_text[i + _window - 1]);

      int ith_hash = old_hash - left_l_hash + right_l_hash;
      _checksums.push_back(ith_hash);
    }
  }

  std::vector<int> find() {
    std::vector<int> results;

    int pattern_checksum = checksum(_pattern);
    precompute_hashes();
    for (int i = 0; i < _scan_bound; ++i) {
      if (pattern_checksum == _checksums[i]) {
        if (_pattern == _text.substr(i, _window)) {
          results.push_back(i);
        }
      }
    }

    return results;
  }
};

int main() {
  std::string pattern, text;
  std::cin >> pattern >> text;

  RabinKarp rk(pattern, text);
  std::vector<int> res = rk.find();

  for (int i = 0; i < res.size(); ++i) {
    std::cout << res[i];
    if (i < res.size() - 1)
      std::cout << " ";
  }
  std::cout << std::endl;

  return 0;
}
