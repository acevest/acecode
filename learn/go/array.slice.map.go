package main

import "fmt"
import "math/rand"

type Vector struct {
	x, y uint32
}

// map在使用前必须使用make而不是new来创建,值为nil的map是空的，并且不能赋值
var Map map[string]Vector

func main() {
	// [n]T 表示array
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
	// []T 表示slice
	var slice []string
	fmt.Println("Slice len", len(slice), "cap", cap(slice))
	// slice 的零值是 `nil`。
	if slice == nil {
		fmt.Println("Slice is nil")
	}
	slice = array[:]
	fmt.Println(slice)
	fmt.Println("Slice len", len(slice), "cap", cap(slice))

	// 清空slice
	slice = nil
	fmt.Println("Slice len", len(slice), "cap", cap(slice))

	// 构造slice
	S := make([]int, 5 /*length*/, 10 /*cap*/) // cap >= length
	fmt.Println("Slice s len", len(S), "cap", cap(S))

	d := []byte{'a', 'b', 'c'}
	fmt.Println(d)
	var e []string = []string{"a", "b", "c"}

	// 向slice中添加元素
	e = append(e, "append:d")
	e = append(e, "append:e", "append:f")

	// 切片复制
	var f []string
	copy(f, e)

	for i := 0; i < len(e); i++ {
		fmt.Println(e[i])
	}

	// range
	for i, v := range d {
		fmt.Println(i, v)
	}

	// 如果只需要索引值，去掉`value`部分就可以了
	for i := range e {
		fmt.Println(i)
	}

	// 如果只需要`value`部分，索引部分可以直接用`_`来忽略
	for _, v := range e {
		fmt.Println(v)
	}

	if Map == nil {
		fmt.Println("Map is nil")
	}
	Map = make(map[string]Vector, 100)
	if Map == nil {
		fmt.Println("Map is nil")
	} else {
		fmt.Println("Map is not nil")
	}
	Map["LeftTop"] = Vector{0, ^uint32(0)}
	Map["LeftBottom"] = Vector{0, 0}
	Map["RightBottom"] = Vector{^uint32(0), 0}
	Map["RightTop"] = Vector{^uint32(0), ^uint32(0)}

	fmt.Println(Map)
	fmt.Println(Map["RightTop"])
	fmt.Println(Map["RightTops"])

	var MapA = map[string]string{
		"Apple":   "USA",
		"Google":  "USA",
		"Tencent": "CHN",
	}

	fmt.Println(MapA)

	// insert
	MapA["Test"] = "Unknown"
	fmt.Println(MapA)

	// modify
	MapA["Test"] = "USA"
	fmt.Println(MapA)

	if s, ok := MapA["Test"]; !ok {
		fmt.Printf("Key:Test not in\n")
	} else {
		fmt.Printf("Key:Test = %s\n", s)
	}

	for key, val := range MapA {
		fmt.Printf("%-10s => %10s\n", key, val)
	}

	// delete
	delete(MapA, "Test")
	fmt.Println(MapA)

	if _, ok := MapA["Test"]; !ok {
		fmt.Println("Key:Test not in")
	}

	AboutSlice()
	AboutMap()
}

func AboutSlice() {
	var array [10]int
	var slice []int = array[2:5]

	for i := 0; i < len(array); i++ {
		array[i] = i
	}

	for i := 0; i < len(slice); i++ {
		fmt.Printf("Slice at %02d is %4d\n", i, slice[i])
	}

	fmt.Println("The Length of Array is", len(array))
	fmt.Println("The Length of Slice is", len(slice))
	fmt.Println("The Capacity of Slice is", cap(slice))

	// grow the slice
	slice = slice[:4]
	for i, v := range slice {
		fmt.Printf("Slice at %02d is %4d\n", i, v)
	}

	fmt.Println("The Length of Slice is", len(slice))
	fmt.Println("The Capacity of Slice is", cap(slice))

}

func AboutMap() {
	{
		// Version A
		items := make([]map[int]int, 5)
		for i := range items {
			items[i] = make(map[int]int, 1)
			items[i][rand.Intn(100)] = rand.Intn(100)
		}

		fmt.Printf("Version A: Value of items: %v\n", items)
	}

	{
		// Version B
		// Invalid Method
		items := make([]map[int]int, 5)
		for _, item := range items {
			item = make(map[int]int, 1)
			item[rand.Intn(100)] = rand.Intn(100)
		}

		fmt.Printf("Version B: Value of items: %v (Invalid Method) \n", items)
	}
}
