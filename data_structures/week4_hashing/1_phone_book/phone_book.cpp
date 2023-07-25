#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::string;
using std::vector;

namespace phone_book {
struct Query {
  string type, name;
  int number;
};

vector<Query> read_queries() {
  int n;
  cin >> n;
  vector<Query> queries(n);
  for (int i = 0; i < n; ++i) {
    cin >> queries[i].type;
    if (queries[i].type == "add")
      cin >> queries[i].number >> queries[i].name;
    else
      cin >> queries[i].number;
  }
  return queries;
}

void write_responses(const vector<string>& result) {
  for (size_t i = 0; i < result.size(); ++i)
    std::cout << result[i] << std::endl;
}

vector<string> process_inefficient(const vector<Query>& queries) {
  vector<Query> contacts;
  vector<string> result;

  for (size_t i = 0; i < queries.size(); ++i)
    if (queries[i].type == "add") {
      bool found = false;

      for (size_t j = 0; j < contacts.size(); ++j)
        if (contacts[j].number == queries[i].number) {
          contacts[j].name = queries[i].name;
          found = true;
          break;
        }

      if (!found)
        contacts.push_back(queries[i]);

    } else if (queries[i].type == "del") {
      for (size_t j = 0; j < contacts.size(); ++j)
        if (contacts[j].number == queries[i].number) {
          contacts.erase(contacts.begin() + j);
          break;
        }

    } else {
      string response = "not found";
      for (size_t j = 0; j < contacts.size(); ++j)
        if (contacts[j].number == queries[i].number) {
          response = contacts[j].name;
          break;
        }
      result.push_back(response);
    }

  return result;
}

vector<string> process(const vector<Query>& queries) {
  std::unordered_map<int, string> contact_map;
  vector<string> result;

  for (const Query& cur_query : queries) {
    if (cur_query.type == "add") {
      contact_map[cur_query.number] = cur_query.name;
    } else if (cur_query.type == "del") {
      contact_map.erase(cur_query.number);
    } else {
      auto it = contact_map.find(cur_query.number);
      if (it != contact_map.end()) {
        result.push_back(it->second);
      } else {
        result.push_back("not found");
      }
    }
  }

  return result;
}
}  // namespace phone_book

int main() {
  phone_book::write_responses(phone_book::process(phone_book::read_queries()));
  return 0;
}
