def calc_fib_naive(n: int) -> int:
    return n if n <= 1 else calc_fib_naive(n - 1) + calc_fib_naive(n - 2)


def calc_fib_fast(n: int) -> int:
    if n <= 1:
        return n

    fib_nums: list[int] = [0, 1]

    for i in range(2, n + 1):
        fib_nums.append(fib_nums[i - 1] + fib_nums[i - 2])

    return fib_nums[n]


if __name__ == "__main__":
    n = int(input())
    print(calc_fib_fast(n))
