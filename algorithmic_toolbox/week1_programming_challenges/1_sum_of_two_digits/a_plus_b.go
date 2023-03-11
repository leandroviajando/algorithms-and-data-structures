package main

import (
	"C"
	"fmt"
)

func main() {
	var a, b int
	fmt.Scanf("%d", &a)
	fmt.Scanf("%d", &b)
	sum := a + b
	fmt.Printf("%d", sum)
}
