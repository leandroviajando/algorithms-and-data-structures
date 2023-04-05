package main

import (
	"C"
	"fmt"
)

func getChange(m int) int {
	n := m % 10
	o := n % 5

	return m/10 + n/5 + o/1
}

func main() {
	var m int
	fmt.Scan(&m)
	fmt.Println(getChange(m))
}
