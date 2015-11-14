package main

import (
	"fmt"
	"runtime"
	"time"
    "math/rand"
)

func main() {
    rand.Seed(time.Now().UnixNano())
	fmt.Print("Go runs on ")
	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OS X.")
	case "linux":
		fmt.Println("Linux.")
	default:
		// freebsd, openbsd,
		// plan9, windows...
		fmt.Printf("%s.", os)
	}

    // switch 可以没有表达示，将变为一个更清晰的if-then-else的代码结构
	t := time.Now()
	switch {
	case t.Hour() < 12:
		fmt.Println("Good morning!")
	case t.Hour() < 17:
		fmt.Println("Good afternoon.")
	default:
		fmt.Println("Good evening.")
	}

    //fallthrough
    switch v:=rand.Intn(4); v {
    case 0:
        fmt.Println("Level0")
        fallthrough
    case 1:
        fmt.Println("Level1")
        fallthrough
    case 2:
        fmt.Println("Level2")
        fallthrough
    case 3:
        fmt.Println("Level3")
        fallthrough
    default:
        fmt.Println("Ground")
    }


}
