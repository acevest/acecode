/*
 * ------------------------------------------------------------------------
 *   File Name: closure.go
 *      Author: Zhao Yanbai
 *              2019-03-18 11:01:25 星期一 CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
	"fmt"
)


func Accumulate(value int) func() int {
    return func() int {
        value++;
        return value;
    }
}

func main() {
	defer fmt.Println("Program Exited...")

    accumulatorA := Accumulate(1)

    fmt.Println(accumulatorA())
    fmt.Println(accumulatorA())

    fmt.Printf("%p\n", accumulatorA);


    accumulatorB := Accumulate(1024)

    fmt.Println(accumulatorB())
    fmt.Println(accumulatorB())

    fmt.Printf("%p\n", accumulatorB);
}
