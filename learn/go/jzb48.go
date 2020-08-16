// Package main
/*
 * ------------------------------------------------------------------------
 *   File Name: jzb48.go
 *      Author: Zhao Yanbai
 *              2020-07-25 21:02:30 星期六 CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"time"

	"github.com/acevest/acgo"
)

func main() {
	defer fmt.Println("Program Exited...")

	ticker := time.NewTicker(60 * time.Second)

	fd, _ := os.OpenFile("jzb48.txt", os.O_RDWR|os.O_CREATE|os.O_APPEND, 0644)
	defer fd.Close()

	for t := range ticker.C {
		r := fetchData("http://www.jzb48.com/zx/api/get.php?type=detail&name=孙珍妮")
		fmt.Fprintf(fd, "%v %v %v\n", t.Format("2006-01-02 15:04:05"), r.Rank, r.Amount)
	}
}

// Result sadfasd
type Result struct {
	Rank   int     `json:"pai"`
	Amount float32 `json:"amount_info"`
}

func fetchData(url string) (r Result) {
	client := &http.Client{}

	req, err := http.NewRequest("GET", url, nil)
	if err != nil {
		log.Fatalln(err)
	}

	ua := acgo.GetRandUserAgent()
	req.Header.Set("User-Agent", ua)

	res, err := client.Do(req)
	if err != nil {
		log.Fatalln(err)
	}

	defer res.Body.Close()

	if res.StatusCode != http.StatusOK {
		log.Printf("http return %v\n", res.StatusCode)
	}

	rsp, _ := ioutil.ReadAll(res.Body)

	// 如果不加这一句就会报下面这个错
	// invalid character 'ï' looking for beginning of value
	// 原因是：
	// The server is sending you a UTF-8 text string with a Byte Order Mark (BOM).
	// The BOM identifies that the text is UTF-8 encoded, but it should be removed before decoding.
	// rsp = bytes.TrimPrefix(rsp, []byte("\xef\xbb\xbf"))
	rsp = acgo.TrimHTTPRspBom(rsp)
	err = json.Unmarshal(rsp, &r)
	if err != nil {
		fmt.Printf("ERR: %v\n", err)
	}

	return
}
