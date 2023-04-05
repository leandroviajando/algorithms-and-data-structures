package main

import (
	"C"
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

func compare(x, y string) bool {
	return x+y > y+x
}

func largestNumber(a []string) string {
	sort.Slice(a, func(i, j int) bool {
		return compare(a[i], a[j])
	})
	var sb strings.Builder
	for _, s := range a {
		sb.WriteString(s)
	}
	return sb.String()
}

func main() {
	var n int
	fmt.Scan(&n)
	a := make([]string, n)
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanWords)
	for i := 0; i < n; i++ {
		scanner.Scan()
		a[i] = scanner.Text()
	}
	fmt.Println(largestNumber(a))
}
