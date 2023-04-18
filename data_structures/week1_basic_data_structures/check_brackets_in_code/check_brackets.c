#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bracket {
  char type;
  int position;
} Bracket;

bool match(char opening_bracket, char closing_bracket) {
  return (opening_bracket == '(' && closing_bracket == ')') ||
         (opening_bracket == '[' && closing_bracket == ']') ||
         (opening_bracket == '{' && closing_bracket == '}');
}

int check_brackets(char text[]) {
  Bracket opening_brackets_stack[strlen(text)];
  int stack_top = -1;

  for (int i = 0; i < strlen(text); i++) {
    char next_char = text[i];
    if (next_char == '(' || next_char == '[' || next_char == '{') {
      Bracket b;
      b.type = next_char;
      b.position = i + 1;
      opening_brackets_stack[++stack_top] = b;
    } else if (next_char == ')' || next_char == ']' || next_char == '}') {
      if (stack_top == -1)
        return i + 1;

      Bracket top = opening_brackets_stack[stack_top];
      if (match(top.type, next_char))
        stack_top--;
      else
        return i + 1;
    }
  }

  if (stack_top == -1)
    return 0;
  else
    return opening_brackets_stack[0].position;
}

int main() {
  char text[100001];
  fgets(text, 100001, stdin);
  int result = check_brackets(text);

  if (result == 0)
    printf("Success\n");
  else
    printf("%d\n", result);

  return 0;
}
