/*
 * ------------------------------------------------------------------------
 *   File Name: clock.go
 *      Author: Zhao Yanbai
 *              2017-05-29 12:35:49 星期一 CST
 * Description: none
 * ------------------------------------------------------------------------
 */

package main

import (
    "io"
    "fmt"
    "net"
    "log"
    "time"
    "math/rand"
    "strconv"
)

func main() {
    defer fmt.Println("Clock Server Exited..")

    listener, err := net.Listen("tcp", ":8000")
    if err != nil {
        log.Fatal(err)
    }

    for {
        conn, err := listener.Accept()
        if err != nil {
            log.Print(err)
            continue
        }

        go handleConn(conn)
    }
}


func handleConn(c net.Conn) {
    defer c.Close()

    for {
        _, err := io.WriteString(c, time.Now().Format("2006-01-02 15:04:05\n"))
        if err != nil {
            return
        }

        _, err = io.WriteString(c, strconv.Itoa(rand.Int())+"\n")
        if err != nil {
            return
        }

        time.Sleep(1 * time.Second)
        time.Sleep(100 * time.Millisecond);
    }
}
