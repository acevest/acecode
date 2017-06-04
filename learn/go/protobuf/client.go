/*
 * ------------------------------------------------------------------------
 *   File Name: client.go
 *      Author: Zhao Yanbai
 *              2017-06-04 17:48:32 Sunday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
	"fmt"
	"log"
	"net"
	"io"

	"github.com/golang/protobuf/proto"
)

func main() {
	defer fmt.Println("Program Exited...")

	sampleData := sample.SampleData {
		Title : "test golang protobuf",
		Type : SAMPLE_TYPE_TEST,
		Data : [1.414, 2.732, 3.14, 6.18],
	}

	data, err := proto.Marshal(sampleData)
	if err != nil {
		log.Fatal("marshaling error: ", err)
	}

	conn, err := net.Dial("tcp", ":8000")
	if err != nil {
		log.Fatal(err)
	}

	defer conn.Close()

	if _, err := io.Copy(conn, data) {
		log.Fatal(err)
	}
}
