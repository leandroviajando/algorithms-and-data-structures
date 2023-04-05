package main

import (
	"C"
	"fmt"
)

func getFibonacciLastDigitNaive(n int) int {
	if n <= 1 {
		return n
	}

	previous := 0
	current := 1

	for i := 0; i < n-1; i++ {
		tmpPrevious := previous
		previous = current
		current = tmpPrevious + current
	}

	return current % 10
}

func getFibonacciLastDigitOptimized(n int) int {
	if n <= 1 {
		return n
	}

	previous := 0
	current := 1

	for i := 0; i < n-1; i++ {
		tmpPrevious := previous
		previous = current
		current = (tmpPrevious + current) % 10
	}

	return current
}

func main() {
	var n int
	fmt.Scan(&n)

	fmt.Println(getFibonacciLastDigitNaive(n))
	fmt.Println(getFibonacciLastDigitOptimized(n))
}
