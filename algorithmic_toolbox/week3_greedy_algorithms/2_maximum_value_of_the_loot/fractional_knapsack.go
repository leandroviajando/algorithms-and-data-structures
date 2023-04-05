package main

import (
	"C"
	"fmt"
	"sort"
)

type Item struct {
	weight     int
	value      int
	unit_value float64
}

func compare(a, b Item) bool {
	return a.unit_value > b.unit_value
}

func get_optimal_value(capacity int, weights, values []int) float64 {
	weight := 0
	value := 0.0

	items := make([]Item, len(weights))
	for i := range weights {
		items[i] = Item{weights[i], values[i], float64(values[i]) / float64(weights[i])}
	}

	sort.Slice(items, func(i, j int) bool {
		return compare(items[i], items[j])
	})

	for _, item := range items {
		if weight >= capacity {
			break
		}

		units := item.weight
		if item.weight > capacity-weight {
			units = capacity - weight
		}
		weight += units
		value += float64(units) * item.unit_value
	}

	return value
}

func main() {
	var n, capacity int
	fmt.Scan(&n, &capacity)
	values := make([]int, n)
	weights := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&values[i], &weights[i])
	}

	optimal_value := get_optimal_value(capacity, weights, values)

	fmt.Printf("%.10f\n", optimal_value)
}
