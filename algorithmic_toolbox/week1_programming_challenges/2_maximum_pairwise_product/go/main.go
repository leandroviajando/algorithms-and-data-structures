package main

import "fmt"

func main() {
	var n int
	fmt.Scanf("%d", &n)

	numbers := make([]int64, n)
	for i := 0; i < n; i++ {
		var num int64
		fmt.Scanf("%d", &num)
		numbers[i] = num
	}

	result := maxPairwiseProduct(numbers)
	fmt.Println(result)
}
