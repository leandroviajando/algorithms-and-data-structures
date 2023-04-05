package main

import (
	"C"
	"fmt"
)

func getFibonacciHugeNaive(n, m int64) int64 {
	if n <= 1 {
		return n
	}

	var previous, current int64 = 0, 1

	for i := int64(0); i < n-1; i++ {
		tmpPrevious := previous
		previous = current
		current = (tmpPrevious + current) % m
	}

	return current
}

func getPisanoPeriod(m int64) int64 {
	var a, b int64 = 0, 1
	var c int64 = a + b
	var period int64 = 0

	for i := int64(0); i < m*m; i++ {
		c = (a + b) % m
		a = b
		b = c

		if a == 0 && b == 1 {
			period = i + 1
			break
		}
	}

	return period
}

func getFibonacciHuge(n, m int64) int64 {
	pisanoPeriod := getPisanoPeriod(m)
	remainder := n % pisanoPeriod
	return getFibonacciHugeNaive(remainder, m)
}

func main() {
	var n, m int64
	fmt.Scanf("%d %d", &n, &m)

	fmt.Println(getFibonacciHuge(n, m))
	fmt.Println(getFibonacciHugeNaive(n, m))
}
