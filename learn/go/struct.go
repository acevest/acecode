package main

import "fmt"
import "time"
import "math/rand"

type Vertex struct {
	X int
	Y int
}

func main() {
	rand.Seed(time.Now().UnixNano())

	v := Vertex{1, 2}
	fmt.Println(v)
	fmt.Println(Vertex{0xABC, 0xCBA})

	// 通过指针间隔访问的过程是透明的
	p := &v
	p.X = rand.Int()
	p.Y = rand.Int()
	fmt.Println(v)
	v.X, v.Y = p.Y, p.X
	fmt.Println(v.X, v.Y)
}
