package main

import (
	"C"
	"fmt"
)

func getFibonacciPartialSumNaive(from, to int64) int64 {
	sum := int64(0)

	current := int64(0)
	next := int64(1)

	for i := int64(0); i <= to; i++ {
		if i >= from {
			sum += current
		}

		newCurrent := next
		next = next + current
		current = newCurrent
	}

	return sum % 10
}

const pisanoPeriod = 60

// The last digit of the numbers in the Fibonacci Sequence form a pattern that repeats after every 60th number.
// Source: https://www.goldennumber.net/fibonacci-60-repeating-pattern/
func getFibonacciPartialSum(from, to int64) int64 {
	fibNums := make([]int64, pisanoPeriod)
	fibNums[0] = 0
	fibNums[1] = 1

	for i := int64(2); i <= pisanoPeriod; i++ {
		fibNums[i] = fibNums[i-1] + fibNums[i-2]
	}

	from %= pisanoPeriod
	to %= pisanoPeriod

	sum := int64(0)
	for j := from; j <= to; j++ {
		sum += fibNums[j%pisanoPeriod]
		sum %= 10
	}

	return sum
}

func main() {
	var from, to int64
	fmt.Scan(&from, &to)

	fmt.Println(getFibonacciPartialSum(from, to))
	fmt.Println(getFibonacciPartialSumNaive(from, to))
}
