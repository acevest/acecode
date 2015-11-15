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
	"math"
	"math/rand"
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
	for i:=0; i<10; i++ {
		fmt.Printf("Positive: %5d         Negative: %5d\n", pos(i), neg(-i*i))
	}


	// Fibonacci
	fibonacci := Fibonacci()
	for i:=0; i<10; i++ {
		fmt.Printf("%02d - %5d\n", i, fibonacci())
	}
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
		b = a+b
		a = t
		//a, b = b, a+b
		return a
	}

	return innerfunc
}
