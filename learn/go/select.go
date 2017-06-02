/*
 * ------------------------------------------------------------------------
 *   File Name: select.go
 *      Author: Zhao Yanbai
 *              2017-04-06 10:04:54 星期四 CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
    "fmt"
    "sync"
    "time"
	"math/rand"
)

func main() {

    data := make(chan int, 1)

    var wg sync.WaitGroup
    wg.Add(2)

    go func() {
        defer wg.Done()
        totalSize := 0
        for {
            select {
            case n := <-data:
                fmt.Println("Received Data ", n)
                totalSize += n
            default:
                fmt.Println("No Data Received")
            }
            fmt.Println("Received Total Size: ", totalSize)
            time.Sleep(2*time.Second)
            //time.Sleep(3*time.Millisecond)
        }
    }()


    go func() {
        defer wg.Done()
        totalSend := 0
        n := 0
        for i :=0; i<100; i++ {
            r := rand.Intn(100)
            n += r
            select {
            case data<-n:
                fmt.Println("Sent Data " , n)
                totalSend += n
                n = 0
            default:
                fmt.Println("No Data Sent")
            }
            time.Sleep(1*time.Second)
            //time.Sleep(1*time.Millisecond)
        }

        fmt.Println("Sent Total Size: ", totalSend)
    }()

    wg.Wait()
}


