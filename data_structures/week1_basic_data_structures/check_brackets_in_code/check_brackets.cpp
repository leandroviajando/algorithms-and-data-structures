#include <iostream>
#include <stack>
#include <string>

struct Bracket {
  Bracket(char type, int position) : type(type), position(position) {}

  bool Matchc(char c) {
    if (type == '[' && c == ']')
      return true;
    if (type == '{' && c == '}')
      return true;
    if (type == '(' && c == ')')
      return true;
    return false;
  }

  char type;
  int position;
};

int check_brackets(const std::string& text) {
  std::stack<Bracket> opening_brackets_stack;
  for (int position = 0; position < text.length(); ++position) {
    char next = text[position];

    if (next == '(' || next == '[' || next == '{')
      opening_brackets_stack.push(Bracket(next, position));

    if (next == ')' || next == ']' || next == '}') {
      if (opening_brackets_stack.empty() || !opening_brackets_stack.top().Matchc(next))
        return position + 1;
      else if (opening_brackets_stack.top().Matchc(next))
        opening_brackets_stack.pop();
    }
  }

  if (!opening_brackets_stack.empty()) {
    Bracket oldest_bracket = opening_brackets_stack.top();
    opening_brackets_stack.pop();

    while (!opening_brackets_stack.empty()) {
      oldest_bracket = opening_brackets_stack.top();
      opening_brackets_stack.pop();
    };

    return oldest_bracket.position + 1;
  }

  return 0;
}

int main() {
  std::string text;
  getline(std::cin, text);

  int result = check_brackets(text);

  if (result == 0)
    std::cout << "Success" << std::endl;
  else
    std::cout << result << std::endl;

  return 0;
}
