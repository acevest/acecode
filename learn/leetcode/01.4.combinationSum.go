package main

import (
	"fmt"
	"sort"
)

func combinationSum(candidates []int, target int) [][]int {
	sort.Ints(candidates)

	var ret [][]int

	for i := range candidates {
		sum := 0
		stack := make([]int, 0)

		for j := i; j < len(candidates); {
			n := candidates[j]
			for sum+n < target {
				sum += n
				stack = append(stack, n)
			}
			if sum == target {
				ret = append(ret, stack)
				sum := 0
				stack := make([]int, 0)
				j++
			} else if sum < target {
				j++
			} else {
				stack = stack[0 : len(stack)-1]
				sum -= n
			}
		}
	}

	return ret
}

func main() {
	fmt.Println(combinationSum([]int{2, 3, 6, 7}, 7))
	fmt.Println(combinationSum([]int{2, 3, 5}, 8))
}
