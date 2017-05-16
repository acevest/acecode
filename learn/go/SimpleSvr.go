/*
 * ------------------------------------------------------------------------
 *   File Name: SimpleSvr.go
 *      Author: Zhao Yanbai
 *              2017-05-15 23:23:38 Monday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

package main

import (
	// "bufio"
	// "fmt"
	"log"
	"net"
)

func handleConn(conn net.Conn) {
	who := conn.RemoteAddr().String()
	/*
		input := bufio.NewScanner(conn)
		for input.Scan() {

		}
	*/
	//fmt.Println(who)
	log.Print(who + " connected to the server")

	conn.Close()
}

func main() {
	defer log.Print("Program Exited...")
	log.Print("Program Started...")

	//listener, err := net.Listen("tcp", "localhost:6666")
	listener, err := net.Listen("tcp", "10.135.190.233:6666")
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
