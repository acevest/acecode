/*
 * ------------------------------------------------------------------------
 *   File Name: rdserial.go
 *      Author: Zhao Yanbai
 *              2019-04-26 18:09:49 星期五 CST
 * Description: none
 * ------------------------------------------------------------------------
 */

package main

import (
	"flag"
	"fmt"
	"github.com/tarm/serial"
	"log"
)

func main() {
	var port string
	var baud int
	flag.StringVar(&port, "p", "/dev/cu.SLAB_USBtoUART", "serial port")
	flag.IntVar(&baud, "b", 115200, "baud rate default 115200")
	flag.Parse()

	log.Printf("port: %s\n", port)

	c := &serial.Config{Name: port, Baud: baud}
	s, err := serial.OpenPort(c)
	if err != nil {
		log.Fatal(err)
	}

	n, err := s.Write([]byte("test"))
	if err != nil {
		log.Fatal(err)
	}

	for {
		buf := make([]byte, 4096)
		n, err = s.Read(buf)
		if err != nil {
			log.Fatal(err)
		}
		fmt.Printf("%s", string(buf[:n]))
	}
}
