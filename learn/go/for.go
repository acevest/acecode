/*
 * ------------------------------------------------------------------------
 *   File Name: for.go
 *      Author: Zhao Yanbai
 *              2015-11-14 10:31:59 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import "fmt"
import "time"
import "math/rand"

func main() {

	rand.Seed(time.Now().UnixNano())

	// basic for
	sum := 0
	for i := 0; i < 10; i++ {
		sum += i
	}

	fmt.Println("Sum:", sum)

	// 与C语言一样 go 的for 前置、后置条件可以为空
	sum = 1
	for sum <= 1000 {
		sum += sum
	}

	fmt.Println("Sum:", sum)

	// for 也是go的 'while'
	for sum >= 0 {
		sum -= rand.Intn(100)
	}

	fmt.Println("Sum:", sum)

	// 死循环
	// for {
	// }
}
