/*
 * ------------------------------------------------------------------------
 *   File Name: methods.go
 *      Author: Zhao Yanbai
 *              2015-11-14 17:22:24 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
    "fmt"
    "math"
    "time"
    "math/rand"
)

type Vector struct {
	x, y float64
}


// 不用指针型也可以
// 此处于C语言同理，用指针能改变则用指针拷贝
// 用值则用值拷贝，指针一般更有效率，可以修改
// 指向的值
func (v *Vector) Abs() float64 {
	return math.Sqrt(v.x*v.x + v.y*v.y)
}

// 可以将v换成非指针型对比
func (v *Vector) Scale(scale float64) {
	v.x = v.x*scale
	v.y = v.y*scale
}

// fmt中的一个接口
// type Stringer interface {
//	    String() string
// }
// 不能是指针
func (v Vector) String() string {
	return fmt.Sprintf("Vector{x:%.4f, y:%.4f}", v.x, v.y)
}


// 根据现有类型定义专用类型
type FloatType float64;

func (f FloatType) TenTimesInt() int {
	return int(f*10)
}

func main() {
    defer fmt.Println("Program Exited...")

	rand.Seed(time.Now().UnixNano())

	v1 := Vector{rand.Float64(), rand.Float64()}
	var v2 Vector = Vector{rand.Float64(), rand.Float64()}

	fmt.Println(v1)
	fmt.Println(v2)

	v1.Scale(10.0)
	v2.Scale(0.9)

	fmt.Println(v1)
	fmt.Println(v2)

	fmt.Println(v1.Abs())
	fmt.Println(v2.Abs())


	f := FloatType(rand.Float64())
	fmt.Printf("Float: %7.4f  Ten Times Integer: %2d\n", f, f.TenTimesInt())
}
