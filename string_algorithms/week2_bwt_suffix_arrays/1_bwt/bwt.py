def bwt(text: str) -> str:
    rotations = [text[i:] + text[:i] for i in range(len(text))]

    rotations.sort()

    return "".join([rotation[-1] for rotation in rotations])


if __name__ == "__main__":
    text = input()
    print(bwt(text))
