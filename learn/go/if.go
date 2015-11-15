/*
 * ------------------------------------------------------------------------
 *   File Name: if.go
 *      Author: Zhao Yanbai
 *              2015-11-14 10:58:10 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	rand.Seed(time.Now().UnixNano())

	n := rand.Int()
	if n%2 == 0 {
		fmt.Println("Even:", n)
	} else {
		fmt.Println("Odd:", n)
	}

	// if 语句在条件之前可以执行一条简单的代码
	if v := rand.Int(); v%3 == 0 {
		fmt.Println(v, " MOD 3 == 0")
	} else if v%3 == 1 {
		fmt.Println(v, " MOD 3 == 1")
	} else {
		fmt.Println(v, " MOD 3 == 2")
	}
}
