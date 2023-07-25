#include <iostream>
#include <vector>

using namespace std;

const int prime = 31;

class Solver {
  string s;
  vector<int> hash_values;

  int calculate_hash(int a, int l) {
    return hash_values[a + l] - hash_values[a];
  }

 public:
  Solver(string s) : s(s), hash_values(s.size() + 1) {
    hash_values[0] = 0;
    for (int i = 0; i < s.size(); ++i)
      hash_values[i + 1] = hash_values[i] + (s[i] - 'a' + 1);
  }

  bool ask(int a, int b, int l) {
    return calculate_hash(a, l) == calculate_hash(b, l);
  }
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);

  string s;
  int q;
  cin >> s >> q;

  Solver solver(s);

  for (int i = 0; i < q; i++) {
    int a, b, l;
    cin >> a >> b >> l;

    cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
  }

  return 0;
}
