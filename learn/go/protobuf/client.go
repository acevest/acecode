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
	//"github.com/acecode/learn/go/protobuf/sample"
	"./sample"
	"github.com/golang/protobuf/proto"
)

func main() {
	defer fmt.Println("Program Exited...")

	dataType := sample.SampleType_SAMPLE_TYPE_TEST
	title := "test golang protobuf"
	sampleData := &sample.SampleData {
		Title : &title,
		Type : &dataType,
		Data : []float64{1.414, 2.732, 3.14, 6.18},
		Source: &sample.SampleData_Source {
			Band: proto.String("Ace"),
			Version: proto.String("1.2"),
		},
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

	fmt.Println("Data Len: ", len(data))
	if _, err := conn.Write(data); err != nil {
		log.Fatal(err)
	}
}
