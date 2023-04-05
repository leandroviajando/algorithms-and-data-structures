package main

import (
	"C"
	"fmt"
	"testing"
)

func fibonacciNaive(n int) int {
	if n <= 1 {
		return n
	}
	return fibonacciNaive(n-1) + fibonacciNaive(n-2)
}

func fibonacciFast(n int) int {
	if n <= 1 {
		return n
	}

	fibNums := make([]int, n+1)
	fibNums[0] = 0
	fibNums[1] = 1

	for i := 2; i <= n; i++ {
		fibNums[i] = fibNums[i-1] + fibNums[i-2]
	}

	return fibNums[n]
}

func testSolution(t *testing.T) {
	assertEqual := func(a, b int) {
		if a != b {
			t.Errorf("expected %d but got %d", b, a)
		}
	}

	assertEqual(fibonacciFast(3), 2)
	assertEqual(fibonacciFast(10), 55)
	for n := 0; n < 20; n++ {
		assertEqual(fibonacciFast(n), fibonacciNaive(n))
	}
}

func main() {
	var n int
	fmt.Scan(&n)

	fmt.Println(fibonacciNaive(n))
	fmt.Println(fibonacciFast(n))
	testSolution(nil)

	fmt.Println("OK")
}
