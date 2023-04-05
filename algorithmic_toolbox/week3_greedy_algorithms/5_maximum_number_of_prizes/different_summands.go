package main

import (
	"C"
	"fmt"
)

func optimalSummands(n int) []int {
	var summands []int

	for i := 1; i <= n; i++ {
		if n-i > i {
			summands = append(summands, i)
			n -= i
		} else {
			summands = append(summands, n)
			break
		}
	}

	return summands
}

func main() {
	var n int
	fmt.Scan(&n)

	summands := optimalSummands(n)

	fmt.Println(len(summands))
	for _, s := range summands {
		fmt.Printf("%d ", s)
	}
}
