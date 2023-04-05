package main

import (
	"C"
	"fmt"
	"sort"
)

func maxDotProduct(a, b []int) int64 {
	sort.Ints(a)
	sort.Ints(b)

	var result int64 = 0
	for i := 0; i < len(a); i++ {
		result += int64(a[i]) * int64(b[i])
	}

	return result
}

func main() {
	var n int
	fmt.Scan(&n)
	a := make([]int, n)
	b := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}
	for i := 0; i < n; i++ {
		fmt.Scan(&b[i])
	}
	fmt.Println(maxDotProduct(a, b))
}
