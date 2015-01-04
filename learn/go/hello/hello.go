package main

import "fmt"
import "math/rand"
import "time"

func main() {
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < rand.Intn(10); i++ {
		fmt.Printf("Hello World\n")
	}
}
