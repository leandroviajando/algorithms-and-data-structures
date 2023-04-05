package main

import (
	"C"
	"fmt"
)

func gcd(a, b int) int {
	var tmp int
	for b != 0 {
		tmp = b
		b = a % b
		a = tmp
	}
	return a
}

func lcm(a, b int) int64 {
	return int64(a) * int64(b) / int64(gcd(a, b))
}

func main() {
	var a, b int
	fmt.Scan(&a, &b)
	fmt.Println(lcm(a, b))
}
