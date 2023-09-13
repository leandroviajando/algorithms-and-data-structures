def evalt(a: int, b: int, op: str) -> int:  # noqa: C901
    if op == "+":
        return a + b

    if op == "-":
        return a - b

    if op == "*":
        return a * b

    raise AssertionError()


def get_maximum_value(dataset: str) -> int:
    return 0


if __name__ == "__main__":
    print(get_maximum_value(input()))
