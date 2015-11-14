package main

import "fmt"
import "math/rand"
import "time"

func GetStr() (string, string) {
    // 常量可以是数字、字符串、布尔或字符
	const stra = "Hello"
	const strb string = "World"
	return stra, strb
}

// 多常量
const (
    BigInt  = 1 << 9
    ConstStr= "HELLO WORLD"
)

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


func Add(a int, b int) int {
    return a+b
}


// 当两个或多个连续参数是同一类型，除了最后一个类型之外，其它的都可以省略
func SwapString(a, b string) (string, string) {
    return b, a
}


// 返回值可以被命名
func Split(sum int) (a, b int) {
    a = sum * 4 / 9
    b = sum - a
    return
}


// 定义变量
var va, vb, vc string

// 定义变量+初始化
var ia, ib, ic rune = 1, 0xFAD, 434
var fa float64 = 2.71828182846
var xa, xb, xc = true, "xb", 0xDD


func main() {
    // defer 的参数会立刻生成，但是只是在程序结束时调用
	defer fmt.Println("----------------")
	rand.Seed(time.Now().UnixNano())
    n := 0
	for i := 0; i < rand.Intn(10)+1; i++ {
		fmt.Println(GetStr())
        n = i
	}

    // defer 会逆序调用
    defer fmt.Println("n:", n)

	PrintType()

    fmt.Println(Add(3, 543))

    fmt.Println(SwapString("Hello", "World"))

    fmt.Println(Split(342))


    va = "va"
    vb = "vb"
    vc = "vc"
    fmt.Println(va, vb, vc)

    fmt.Println(ia, ib, ic)

    fmt.Println(fa)

    fmt.Println(xa, xb, xc)


    // 短声明,只能用在函数内部
    sa := 34
    // 类型推导
    sb := sa
    fmt.Println(sa, sb)

    // 强制类型转换
    sc := float64(sa)
    fmt.Println(sc)

    // 常量不能用:=语法定义
    // const sd := sa

    fmt.Println(BigInt, ConstStr)



    // 指针, go 语言没有指针运算
    var pi *int
    pj := &n
    pi = pj

    *pj = 123

    fmt.Println(n, *pi, *pj, pi, pj)
}
