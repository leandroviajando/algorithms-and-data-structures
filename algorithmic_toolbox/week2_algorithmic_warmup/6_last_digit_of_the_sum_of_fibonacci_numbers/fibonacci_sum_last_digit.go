package main

import (
	"C"
	"fmt"
)

func fibonacci_sum_naive(n int64) int {
	if n <= 1 {
		return int(n)
	}

	var previous, current, sum int64 = 0, 1, 1

	for i := int64(0); i < n-1; i++ {
		tmp_previous := previous
		previous = current
		current = tmp_previous + current
		sum += current
	}

	return int(sum % 10)
}

// The last digit of the numbers in the Fibonacci Sequence form a pattern that repeats after every 60th number.
// Source: https://www.goldennumber.net/fibonacci-60-repeating-pattern/
func fibonacci_sum(n int64) int {
	return fibonacci_sum_naive(n % 60)
}

func main() {
	var n int64
	fmt.Scanln(&n)

	fmt.Println(fibonacci_sum(n))
	fmt.Println(fibonacci_sum_naive(n))
}
