import sys

if __name__ == "__main__":
    tokens = sys.stdin.read().split()
    a = int(tokens[0])
    b = int(tokens[1])
    _sum = a + b
    print(_sum)
