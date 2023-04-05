package main

import (
	"C"
	"fmt"
)

func gcdNaive(a, b int) int {
	currentGcd := 1

	for d := 2; d <= a && d <= b; d++ {
		if a%d == 0 && b%d == 0 {
			if d > currentGcd {
				currentGcd = d
			}
		}
	}

	return currentGcd
}

func gcdEuclidean(a, b int) int {
	min := a
	max := b
	if a > b {
		min = b
		max = a
	}

	if min == 0 {
		return max
	}

	return gcdEuclidean(max%min, min)
}

func main() {
	var a, b int
	fmt.Scan(&a, &b)

	fmt.Println(gcdNaive(a, b))
	fmt.Println(gcdEuclidean(a, b))
}
