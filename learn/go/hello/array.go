package main

import "fmt"

func main() {
	var array [2]string
	array[0] = "HELLO"
	array[1] = "GO"

	fmt.Println(array[0], array[1])
	fmt.Println(array)

	var a int = 1
	fmt.Println(a)
	b := [2]string{"haha", "hehe"}
	var c [2]string = [2]string{"a", "b"}
	// ERROR: var c [2]string = {"a", "b"}
	fmt.Println(b)
	fmt.Println(c)

	// SLICE
	d := []byte{'a', 'b', 'c'}
	fmt.Println(d)
	var e []string = []string{"a", "b", "c"}

	for i := 0; i < len(e); i++ {
		fmt.Println(e[i])
	}
}
