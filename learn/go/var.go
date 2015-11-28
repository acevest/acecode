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
}
