/*
 * ------------------------------------------------------------------------
 *   File Name: reflect.go
 *      Author: Zhao Yanbai
 *              2017-05-31 21:24:09 Wednesday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
	"fmt"
	"reflect"
)

func main() {
	defer fmt.Println("Program Exited...")

	var a float32 = 6.18
	v := reflect.ValueOf(a)	// Copy

	fmt.Printf("Type %s Value %v Value %f Value %s\n", reflect.TypeOf(a), v, v, v.String()) // reflect.ValueOf(a), reflect.ValueOf(a).String())

	fmt.Println("Value: ", v)
	fmt.Println("Type: ", v.Type())
	fmt.Println("Value Kind: ", v.Kind())
	fmt.Println("Value: ", v.Float())
	fmt.Println("Interface: ", v.Interface())

	b := v.Interface().(float32)
	fmt.Println(b)


	// v.SetFloat(3.14) // panic: reflect: reflect.Value.SetFloat using unaddressable value

	fmt.Println("Settability of v:", v.CanSet())


	p := reflect.ValueOf(&a)
	fmt.Println("Type of p:", p.Type())
	fmt.Println("Settability of p:", p.CanSet())
	fmt.Println("The Element Of p:", p.Elem())
	fmt.Println("Settability of p.Elem:", p.Elem().CanSet())
	p.Elem().SetFloat(3.14)
	fmt.Println("p.Elem.Interface:", p.Elem().Interface())
	fmt.Println("p.Elem:", p.Elem())
	fmt.Println("a:", a)
}
