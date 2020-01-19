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
	"os"
    "time"
)

func main() {
	var port string
	var baud int
	var outfile string
	flag.StringVar(&port, "p", "/dev/cu.SLAB_USBtoUART", "serial port")
	flag.IntVar(&baud, "b", 115200, "baud rate default 115200")
	flag.StringVar(&outfile, "o", "/dev/null", "output file path")
	flag.Parse()

	log.Printf("port: %s\n", port)

	//c := &serial.Config{Name: port, Baud: baud}
	c := &serial.Config{Name: port, Baud: baud}
	s, err := serial.OpenPort(c)
	if err != nil {
		log.Fatal(err)
	}

	f, err := os.OpenFile(outfile, os.O_CREATE|os.O_RDWR|os.O_APPEND, 0600)
	if err != nil {
		log.Fatalf("open file failed: %s\n", err)
	}
	defer f.Close()

    time.Sleep(1*time.Second)
    s.Write([]byte("ATE0\r\n"))
    time.Sleep(1*time.Second)
    s.Write([]byte("AT\r\n"))
    time.Sleep(1*time.Second)
	for {
		buf := make([]byte, 4096)
		n, err := s.Read(buf)
		if err != nil {
			log.Fatal(err)
		}
		fmt.Printf("%s", string(buf[:n]))
		f.Write(buf[:n])
	}
}
