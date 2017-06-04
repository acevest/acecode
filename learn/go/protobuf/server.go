/*
 * ------------------------------------------------------------------------
 *   File Name: server.go
 *      Author: Zhao Yanbai
 *              2017-06-04 17:48:30 Sunday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
	"fmt"
	"net"
	"log"
	"github.com/golang/protobuf/proto"
	"./sample"
)

func main() {
	defer fmt.Println("Program Exited...")
	listener, err := net.Listen("tcp", ":8000")
	if err != nil {
		log.Fatal(err)
	}

	conn, err := listener.Accept()
	if err != nil {
		log.Fatal(err)
	}

	defer conn.Close()

	//var data []byte	这里一定要指定缓冲区大小
	data := make([]byte, 4096)
	if n, err := conn.Read(data); err != nil {
		log.Fatal("conn.Read: ", err)
	} else {
		log.Println("Recevied Len: ", n)
		data = data[:n]
	}

	fmt.Println("Data Len: ", len(data))

	sampleData := sample.SampleData{ }
	err = proto.Unmarshal(data, &sampleData)
	if err != nil {
		log.Fatal("proto.Unmarshal: ", err)
	}

	fmt.Println("Title: ", sampleData.GetTitle())
	fmt.Println("Type: ", sampleData.GetType())
	fmt.Printf("Data: ")
	for i, v := range(sampleData.GetData()) {
		if i > 0 {
			fmt.Printf(" ")
		}

		fmt.Printf("%v", v)
	}

	fmt.Println("")
	fmt.Println("Source.Band: ", sampleData.GetSource().GetBand())
	fmt.Println("Source.Version: ", sampleData.GetSource().GetVersion())
}
