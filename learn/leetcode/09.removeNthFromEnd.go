package main

import (
	"fmt"
	"math/rand"
	"time"
)

// ListNode list node
type ListNode struct {
	Val  int
	Next *ListNode
}

func removeNthFromEnd(head *ListNode, n int) *ListNode {
	var poineer *ListNode
	var deleter *ListNode

	poineer = head
	deleter = &ListNode{0, head}

	// 向前移动n个，就和deleter相隔n+1个节点
	// 这样deleter就指向了要删除节点的父节点
	for i := 0; i < n && poineer != nil; i++ {
		poineer = poineer.Next
	}

	// 一次遍历到尾部节点
	for poineer != nil {
		poineer = poineer.Next
		deleter = deleter.Next
	}

	// 删除倒数第n个节点
	if deleter.Next != head {
		deleter.Next = deleter.Next.Next
	} else {
		head = head.Next
	}

	return head
}

func init() {
	rand.Seed(time.Now().UnixNano())
}
func printList(p *ListNode) {
	for p != nil {
		fmt.Printf("%v -> ", p.Val)
		p = p.Next
	}

	fmt.Println("")
}

func lengthOfLastWord(s string) int {
	c := 0
	for i := 0; i < len(s); i++ {
		if s[i] == ' ' {
			c = 0
		} else {
			c++
		}
	}

	return c
}

func reverseBetween(head *ListNode, m int, n int) *ListNode {
	if m == n {
		return head
	}

	T := &ListNode{0, head}

	ph := T
	pe := T.Next
	for i := 1; i < m; i++ {
		ph = ph.Next
		pe = pe.Next
	}
	pt := pe.Next

	for i := 0; i < (n - m); i++ {
		pe.Next = pt.Next
		pt.Next = ph.Next
		ph.Next = pt

		pt = pe.Next
	}

	return T.Next
}

func swapPairs(head *ListNode) *ListNode {
	if head == nil {
		return head
	}

	ph := head
	pt := head.Next

	if pt != nil {
		ph.Next = pt.Next
		pt.Next = ph

		head = pt
	}

	for ph.Next != nil {
		pt := ph.Next.Next
		if pt != nil {
			ph.Next.Next = pt.Next
			pt.Next = ph.Next
			ph.Next = pt

			ph = ph.Next.Next
		} else {
			break
		}
	}

	return head
}

func factorial(n int) int {

	for i := n - 1; i > 1; i-- {
		n *= i
	}
	if n == 0 {
		return 1
	}
	return n
}

func getInxNum() func(int) int {
	nums := []int{1, 2, 3, 4, 5, 6, 7, 8, 9}
	return func(inx int) int {
		c := 0

		for i := 0; i < len(nums); i++ {
			if nums[i] != 0 {
				if c == inx {
					n := nums[i]
					nums[i] = 0
					return n
				}
				c++
			}
		}
		return 0
	}
}
func getPermutation(n int, k int) string {
	getNext := getInxNum()
	ret := 0

	k--

	for i := n; i > 0; i-- {
		FIB := factorial(i - 1)
		div := k / FIB
		mod := k % FIB

		ret = ret*10 + getNext(div)

		k = mod

	}
	return fmt.Sprintf("%v", ret)
}

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	maxN := (len(nums1) + len(nums2) - 1) / 2

	i := 0
	j := 0

	a := 0
	b := 0
	for c := 0; ; c++ {
		if i >= len(nums1) && j < len(nums2) {
			b = nums2[j]
			j++
		} else if j >= len(nums2) && i < len(nums1) {
			b = nums1[i]
			i++
		} else if i < len(nums1) && j < len(nums2) {
			if nums1[i] < nums2[j] {
				b = nums1[i]
				i++
			} else {
				b = nums2[j]
				j++
			}
		}
		if c == maxN+1 {
			break
		}

		a = b
	}
	//fmt.Println(a, b)

	if (len(nums1)+len(nums2))%2 == 0 {
		//fmt.Println("as")
		return float64(a+b) / 2.0
	}

	return float64(a)
}

func main() {
	head := &ListNode{1234, nil}
	p := head

	cnt := rand.Intn(20) + 1 // 保证是大于或等于1的数
	cnt = 6
	for i := 0; i < cnt; i++ {
		p.Next = &ListNode{i, nil}
		p = p.Next
	}
	printList(head)
	p = swapPairs(head)
	printList(p)

	fmt.Println(findMedianSortedArrays([]int{1, 3}, []int{2}))
	fmt.Println(findMedianSortedArrays([]int{1, 2}, []int{3, 4}))
	fmt.Println(findMedianSortedArrays([]int{1}, []int{}))
	fmt.Println(findMedianSortedArrays([]int{1, 2}, []int{}))
	fmt.Println(findMedianSortedArrays([]int{1, 2, 3}, []int{}))
	fmt.Println(findMedianSortedArrays([]int{1, 2, 3}, []int{1, 2, 3}))
}
