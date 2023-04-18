import sys
from typing import Final, Literal, Optional, cast

OPENING_BRACKETS: Final = ("[", "{", "(")

OpeningBracketType = Literal["[", "{", "("]


class Bracket:
    def __init__(self, opening_bracket_type: OpeningBracketType, *, pos: int) -> None:
        self.__opening_bracket_type: Final = opening_bracket_type
        self.position: Final = pos

    def match(self, closing_bracket_type: str) -> bool:  # noqa: FNE005
        return (
            (self.__opening_bracket_type == "[" and closing_bracket_type == "]")
            or (self.__opening_bracket_type == "{" and closing_bracket_type == "}")
            or (self.__opening_bracket_type == "(" and closing_bracket_type == ")")
        )


def check_brackets(text: str) -> Optional[int]:  # noqa: C901
    opening_brackets_stack: list[Bracket] = []

    for i, next_char in enumerate(text, start=1):
        if next_char in ("(", "[", "{"):
            opening_brackets_stack.append(Bracket(cast(OpeningBracketType, next_char), pos=i))

        elif next_char in (")", "]", "}"):  # noqa: SIM102
            if not opening_brackets_stack or not opening_brackets_stack.pop().match(next_char):
                return i

    if opening_brackets_stack:
        return opening_brackets_stack[0].position

    return None


if __name__ == "__main__":
    text = sys.stdin.read()

    print(check_brackets(text) or "Success")
