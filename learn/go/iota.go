/*
 * ------------------------------------------------------------------------
 *   File Name: iota.go
 *      Author: Zhao Yanbai
 *              2015-11-28 14:23:24 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"fmt"
)

const (
	_  = iota
	KB = 1 << (10 * iota)
	MB
	GB
	TB
	PB
	EB
	ZB
	YB
)

const (
	Active = 1 << iota
	Send
	Receive
)

func main() {
	defer fmt.Println("Program Exited...")

	fmt.Printf("0x%X 0x%X 0x%X 0x%X\n", KB, MB, GB, TB)

	fmt.Printf("0x%X 0x%X 0x%X\n", Active, Send, Receive)
}
