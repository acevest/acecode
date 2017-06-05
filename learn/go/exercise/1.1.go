/*
 * ------------------------------------------------------------------------
 *   File Name: 1.1.go
 *      Author: Zhao Yanbai
 *              2017-06-05 23:10:22 Monday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
	"os"
	"fmt"
)

func main() {
	defer fmt.Println("Program Exited...")

	s, sep := "", " "
	for i, arg := range os.Args[:] {
		if i > 0 {
			s += sep
		}

		s += arg
	}

	fmt.Println(s)
}
