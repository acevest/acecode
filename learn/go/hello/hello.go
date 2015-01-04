package main

import "fmt"
import "math/rand"
import "time"

func GetStr() (string, string) {
	const stra = "Hello"
	const strb string = "World"
	return stra, strb
}

func PrintType() {
	var a int
	var b int32
	var c int64
	var d uint32
	var e float32
	var f bool
	var g complex64
	var h complex128

	fmt.Printf("%T %T %T %T %T %T %T %T\n", a, b, c, d, e, f, g, h)
}

func main() {
	defer fmt.Println("----------------")
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < rand.Intn(10)+1; i++ {
		fmt.Println(GetStr())
	}

	PrintType()
}
