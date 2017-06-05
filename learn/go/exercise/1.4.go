/*
 * ------------------------------------------------------------------------
 *   File Name: 1.4.go
 *      Author: Zhao Yanbai
 *              2017-06-05 23:24:57 Monday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
	"os"
	"fmt"
	"log"
	"bufio"
)




func main() {
	defer fmt.Println("Program Exited...")

	files := os.Args[1:]

	if len(files) == 0 {
		countLines(os.Stdin)
	} else {
		for _, file := range(files) {
			fmt.Println("Counting %s\n", file)
			f, err := os.Open(file)
			defer f.Close()
			if err != nil {
				log.Fatal(err)
			}
			countLines(f)
		}
	}
}


func countLines(f *os.File) {
	var counts = make(map[string]int)
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		counts[scanner.Text()]++
	}


	for k, v := range(counts) {
		fmt.Printf("%s:%d\n", k, v)
	}
}
