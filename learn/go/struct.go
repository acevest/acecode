package main

import "fmt"
import "time"
import "math/rand"
import "reflect"

type Private struct {
	data string
}

type Vertex struct {
	X int
	Y int	"Y Pos"	// 字段名可以带标签
	string	"Anonymous Field"	// 匿名字段
	Private "Anonymous Struct"	// 在一个结构体中对于每一种数据类型只能有一个匿名字段
	s string
}

func main() {
	rand.Seed(time.Now().UnixNano())

	v := Vertex{X:1, Y:2}

	v.string = "anonymouse string field"
	v.data   = "anonymouse struct field data"
	fmt.Println(v)
	fmt.Println(Vertex{X:0xABC, Y:0xCBA})
	//fmt.Println(Vertex{0xAA, 0xBB, "anonymous string", {"anonymous data"}, "dd", "FF"})
	fmt.Println(Vertex{0xAA, 0xBB, "anonymous string", Private{"anonymous data"}, "a"})

	// 通过指针间隔访问的过程是透明的
	p := &v
	p.X = rand.Int()
	p.Y = rand.Int()
	fmt.Println(v)
	v.X, v.Y = p.Y, p.X
	fmt.Println(v.X, v.Y)

	// 遍历结构
	fmt.Printf("%10v %16v %16v %10v %10v %16v %10v\n", "Name", "Type", "Tag", "Offset", "Index", "PkgPath", "Anonymous")
	for i := 0; i < reflect.TypeOf(v).NumField(); i++ {
		Field := reflect.TypeOf(v).Field(i)
		fmt.Printf("%10v %16v %16v %10v %10v %16v %10v\n", Field.Name, Field.Type, Field.Tag, Field.Offset, Field.Index, Field.PkgPath, Field.Anonymous)
	}
}
