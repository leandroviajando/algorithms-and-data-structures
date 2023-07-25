#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace hash_chains {
struct Query {
  string type, s;
  size_t idx;
};

class QueryProcessor {
  int bucket_count;
  vector<vector<string>> elems;

  size_t hash_func(const string& s) const {
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;
    unsigned long long hash = 0;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
      hash = (hash * multiplier + s[i]) % prime;
    return hash % bucket_count;
  }

 public:
  explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count), elems(bucket_count) {}

  Query readQuery() const {
    Query query;

    std::cin >> query.type;
    if (query.type != "check")
      std::cin >> query.s;
    else
      std::cin >> query.idx;

    return query;
  }

  void writeSearchResult(bool was_found) const {
    std::cout << (was_found ? "yes\n" : "no\n");
  }

  // vector<string> elems;
  // void processInefficient(const Query& query) {
  //   if (query.type == "check") {
  //     // use reverse order, because we append strings to the end
  //     for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
  //       if (hash_func(elems[i]) == query.idx)
  //         std::cout << elems[i] << " ";
  //     std::cout << std::endl;
  //   } else {
  //     vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
  //     if (query.type == "find")
  //       writeSearchResult(it != elems.end());
  //     else if (query.type == "add") {
  //       if (it == elems.end())
  //         elems.push_back(query.s);
  //     } else if (query.type == "del") {
  //       if (it != elems.end())
  //         elems.erase(it);
  //     }
  //   }
  // }

  void processQuery(const Query& query) {
    if (query.type == "check") {
      // use reverse order, because we append strings to the end
      for (int i = static_cast<int>(elems[query.idx].size()) - 1; i >= 0; --i)
        std::cout << elems[query.idx][i] << " ";
      std::cout << std::endl;
    } else {
      size_t hashed = hash_func(query.s);

      if (query.type == "find") {
        bool found = false;
        for (const string& cur_string : elems[hashed]) {
          if (cur_string == query.s) {
            found = true;
            break;
          }
        }
        writeSearchResult(found);

      } else if (query.type == "add")
        elems[hashed].push_back(query.s);

      else if (query.type == "del")
        elems[hashed].erase(std::remove(elems[hashed].begin(), elems[hashed].end(), query.s), elems[hashed].end());
    }
  }

  void processQueries() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
      processQuery(readQuery());
  }
};
}  // namespace hash_chains

int main() {
  std::ios_base::sync_with_stdio(false);
  int bucket_count;
  std::cin >> bucket_count;

  hash_chains::QueryProcessor proc(bucket_count);
  proc.processQueries();

  return 0;
}
