package main

import (
	"C"
	"fmt"
	"sort"
)

type Segment struct {
	Start int
	End   int
}

type ByEnd []Segment

func (s ByEnd) Len() int {
	return len(s)
}

func (s ByEnd) Swap(i, j int) {
	s[i], s[j] = s[j], s[i]
}

func (s ByEnd) Less(i, j int) bool {
	return s[i].End < s[j].End
}

func optimalPoints(segments []Segment) []int {
	sort.Sort(ByEnd(segments))

	points := make([]int, 0)

	for len(segments) > 0 {
		point := segments[0].End
		points = append(points, point)

		for i := 0; i < len(segments); i++ {
			if segments[i].Start <= point && point <= segments[i].End {
				segments[i] = segments[len(segments)-1]
				segments = segments[:len(segments)-1]
				i--
			}
		}
	}

	return points
}

func main() {
	var n int
	fmt.Scan(&n)

	segments := make([]Segment, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&segments[i].Start, &segments[i].End)
	}

	points := optimalPoints(segments)
	fmt.Println(len(points))
	for _, point := range points {
		fmt.Printf("%d ", point)
	}
}
