package main

import "fmt"

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
	Map = make(map[string]Vector)
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

	var s string
	var ok bool
	s, ok = MapA["Test"]
	if !ok {
		fmt.Printf("Key:Test not in\n")
	} else {
		fmt.Printf("Key:Test = %s\n", s)
	}

	// delete
	delete(MapA, "Test")
	fmt.Println(MapA)

	_, ok = MapA["Test"]
	if !ok {
		fmt.Println("Key:Test not in")
	}
}
