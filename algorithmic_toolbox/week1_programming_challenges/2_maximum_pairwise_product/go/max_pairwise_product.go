package main

func maxPairwiseProduct(numbers []int64) int64 {
	n := len(numbers)

	index1 := 0
	for i := 1; i < n; i++ {
		if numbers[i] > numbers[index1] {
			index1 = i
		}
	}

	index2 := 0
	if index1 == 0 {
		index2 = 1
	}
	for i := 1; i < n; i++ {
		if i != index1 && numbers[i] > numbers[index2] {
			index2 = i
		}
	}

	return numbers[index1] * numbers[index2]
}
