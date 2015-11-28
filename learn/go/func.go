/*
 * ------------------------------------------------------------------------
 *   File Name: func.go
 *      Author: Zhao Yanbai
 *              2015-11-14 15:51:24 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"fmt"
	"io"
	"log"
	"math"
	"math/rand"
	"runtime"
	"time"
)

func main() {
	defer fmt.Println("Program Exited...")

	// 函数也是值
	hypot := func(x, y float64) float64 {
		return math.Sqrt(x*x + y*y)
	}

	rand.Seed(time.Now().UnixNano())
	fmt.Println(hypot(rand.Float64(), rand.Float64()))

	// 闭包

	// 两个闭包实例
	pos := Adder()
	neg := Adder()

	// NOTICE 十次是两个实例的累计结果，不是独立函数调用结果
	for i := 0; i < 10; i++ {
		fmt.Printf("Positive: %5d         Negative: %5d\n", pos(i), neg(-i*i))
	}

	where := func() {
		_, file, line, _ := runtime.Caller(1)
		log.Printf("%s:%d", file, line)
	}

	where()

	// Fibonacci
	fibonacci := Fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Printf("%02d - %5d\n", i, fibonacci())
	}

	where()

	// Vararg Func
	VarArgFuncA("Google", "Apple", "Microsoft", "Tencent")

	RecordRet("Golang")

	where()

	for i := 0; i < 10; i++ {
		fmt.Printf("FibonacciRecursive(%d) is: %4d\n", i, FibonacciRecursive(i))
	}

	where()
}

func Adder() func(int) int {

	sum := 0

	// go语言不能在函数内部显示嵌套定义函数
	// 但是可以定义一个匿名函数
	innerfunc := func(x int) int {
		sum += x
		return sum
	}

	return innerfunc
}

func Fibonacci() func() int {
	a := 0
	b := 1
	// a, b := 0, 1
	innerfunc := func() int {
		t := b
		b = a + b
		a = t
		//a, b = b, a+b
		return a
	}

	return innerfunc
}

// 变长参数函数

// sv 的类型为[]string
func VarArgFuncA(sv ...string) {
	for i, s := range sv {
		fmt.Printf("VarArgFuncA Parameter[%02d]: %s\n", i, s)
	}
}

func RecordRet(s string) (n int, err error) {
	defer func() {
		log.Printf("RecordRet(%q) = %d, %v", s, n, err)
	}()

	return 7, io.EOF
}

// 递归
func FibonacciRecursive(n int) int {
	if n <= 1 {
		return 1
	}

	return FibonacciRecursive(n-1) + FibonacciRecursive(n-2)
}
