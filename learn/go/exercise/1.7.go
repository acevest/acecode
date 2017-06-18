/*
 * ------------------------------------------------------------------------
 *   File Name: 1.7.go
 *      Author: Zhao Yanbai
 *              2017-06-11 17:18:40 Sunday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main
import (
	"net/http"
	"os"
	"io"
	"log"
	"strings"
)

func main() {
	for _, url := range os.Args[1:] {
		if !strings.HasPrefix("http://", url) {
			url = "http://" + url
		}

		rsp, err := http.Get(url)
		if err != nil {
			log.Fatalf("fetch: %s\n", err)
		}

		if n, err := io.Copy(os.Stdout, rsp.Body); err != nil {
			log.Fatalf("reading: %s:%s\n", url, err)
		} else {
			log.Printf("\nread %d bytes. status code: %v\n", n, rsp.Status)
		}
	}

}
