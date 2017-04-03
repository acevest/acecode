/*
 * ------------------------------------------------------------------------
 *   File Name: var.go
 *      Author: Zhao Yanbai
 *              2015-11-28 13:47:31 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"fmt"
	"os"
)

func main() {
	defer fmt.Println("Program Exited...")

	var HOME = os.Getenv("HOME")

	fmt.Println(HOME)

	data := int64(0x11223Ace45566)

	// [1] 是使用第1个参数 # 是指要打印出 0 0x 0X等前缀
	fmt.Printf("%d %[1]x %#[1]x %#[1]X\n", data);

}
