/*
 * ------------------------------------------------------------------------
 *   File Name: main.go
 *      Author: Zhao Yanbai
 *              2021-04-28 17:27:01 Wednesday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

package main

import (
	"fmt"
	"math/big"
)

const chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

func DigitalStringCompress(ds string) string {
	var cs string

	n := big.NewInt(0)

	base := big.NewInt(10)
	for c := range ds {
		n.Mul(n, base)
		n.Add(n, uint64(c))
	}

	return "s"
}

func main() {
	defer fmt.Println("Program Exited...")

}
