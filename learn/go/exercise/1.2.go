/*
 * ------------------------------------------------------------------------
 *   File Name: 1.2.go
 *      Author: Zhao Yanbai
 *              2017-06-05 23:13:55 Monday CST
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
	for i, v := range(os.Args) {
		fmt.Printf("%10d %s\n", i, v)
	}
}
