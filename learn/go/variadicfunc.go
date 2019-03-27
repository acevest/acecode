/*
 * ------------------------------------------------------------------------
 *   File Name: variadicfunc.go
 *      Author: Zhao Yanbai
 *              2019-03-18 15:16:04 星期一 CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
	"fmt"
)

func sum(vals ...int) int {
    total := 0

    for _, v := range(vals) {
        total += v
    }

    return total
}


func rawPrintType(args ...interface{}) {
    for _, s := range args {
        fmt.Printf("%T\n", s)
    }
}


func printType(args ...interface{}) {
    rawPrintType(args...);
}


func main() {
	defer fmt.Println("Program Exited...")

    fmt.Println(sum(1, 2, 3, 4, 5))

    var a struct { }

    printType(1, 1.0, true, a)
}
