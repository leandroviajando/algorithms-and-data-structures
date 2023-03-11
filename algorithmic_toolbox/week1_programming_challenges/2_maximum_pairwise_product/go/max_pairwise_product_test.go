package main

import (
	"fmt"
	"testing"

	"github.com/c2fo/testify/assert"
)

func TestMaxPairwiseProduct(t *testing.T) {
	for _, test := range []struct {
		description string
		inputs      []int64
		expected    int64
	}{
		{
			description: "should calculate max pairwise product",
			inputs:      []int64{5, 6, 7, 4, 2},
			expected:    42,
		},
		{
			description: "should calculate max pairwise product for large numbers",
			inputs:      []int64{90000, 100000},
			expected:    9000000000,
		},
	} {
		t.Run(test.description, func(t *testing.T) {
			assert.Equal(t, test.expected, maxPairwiseProduct(test.inputs), fmt.Sprintf(test.description))
		})
	}
}
