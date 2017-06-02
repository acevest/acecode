/*
 * ------------------------------------------------------------------------
 *   File Name: panic.go
 *      Author: Zhao Yanbai
 *              2017-05-20 12:17:13 星期六 CST
 * Description: none
 * ------------------------------------------------------------------------
 */

package main

import (
	"fmt"
	"os"
	"runtime"
)

func main() {
	defer fmt.Println("Program Exited...")
	defer printStack()
	panicFunc(3)
}

func printStack() {
    var buf [4096]byte
    n := runtime.Stack(buf[:], false)
    os.Stdout.Write(buf[:n])
}

func panicFunc(n int) {
	fmt.Printf("panicFunc(%d)\n", n+0/n)
	defer fmt.Printf("defer panicFunc(%d)\n", n)
	panicFunc(n - 1)
}
