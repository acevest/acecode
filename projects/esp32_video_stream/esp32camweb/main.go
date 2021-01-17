/*
 * ------------------------------------------------------------------------
 *   File Name: main.go
 *      Author: Zhao Yanbai
 *              2021-01-16 23:01:01 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

package main

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
	"time"

	"github.com/gorilla/websocket"
)

var upgrader = websocket.Upgrader{
	ReadBufferSize:  102400,
	WriteBufferSize: 102400,

	// 解决跨域问题
	CheckOrigin: func(r *http.Request) bool {
		return true
	},
}

var frameChan chan []byte

func init() {
	frameChan = make(chan []byte, 32)
}

const (
	partBOUNDARY      = "123456789000000000000987654321"
	streamContentType = "multipart/x-mixed-replace;boundary=" + partBOUNDARY
	streamBoundary    = "\r\n--" + partBOUNDARY + "\r\n"
	streamPart        = "Content-Type: image/jpeg\r\nContent-Length: %d\r\n\r\n"
)

func watchHandler(w http.ResponseWriter, r *http.Request) {
	var err error
	w.Header().Set("Content-Type", streamContentType)
	w.Header().Set("Access-Control-Allow-Origin", "*")

	flusher, _ := w.(http.Flusher)

	for i := 0; ; i++ {
		var data []byte
		select {
		case data = <-frameChan:
			fmt.Fprintf(w, "%v", streamBoundary)
			fmt.Fprintf(w, streamPart, i)
			_, err = w.Write(data)
			flusher.Flush()
			if err != nil {
				break
			}
		default:
			continue
		}

	}
}

func videoHandler(w http.ResponseWriter, r *http.Request) {
	var err error
	var ws *websocket.Conn

	log.Printf("video\n")
	ws, err = upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Printf("err: %v", err)
		return
	}

	defer ws.Close()

	for {
		t, p, e := ws.ReadMessage()
		log.Printf("type %v data len %v err %v", t, len(p), e)
		if e != nil {
			break
		}

		if len(p) < 100 {
			continue
		}

		select {
		case frameChan <- p:
			log.Printf("put frame")
		default:
			log.Printf("drop frame")
		}

	}
}

func streamHandler(w http.ResponseWriter, r *http.Request) {
	var err error
	var ws *websocket.Conn

	ws, err = upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Printf("err: %v", err)
		return
	}

	defer ws.Close()

	for {
		var data []byte
		select {
		case data = <-frameChan:
		case <-time.After(1 * time.Millisecond):
			continue
		}

		err = ws.WriteMessage(websocket.BinaryMessage, data)
		if err != nil {
			break
		}
	}
}

func canvasHandler(w http.ResponseWriter, r *http.Request) {
	tmpl := template.Must(template.ParseFiles("./canvas.html"))
	var data = map[string]interface{}{}
	tmpl.Execute(w, data)
}

func main() {
	defer fmt.Println("Program Exited...")

	m := http.NewServeMux()
	m.HandleFunc("/watch", watchHandler)
	m.HandleFunc("/video", videoHandler)
	m.HandleFunc("/canvas", canvasHandler)
	m.HandleFunc("/stream", streamHandler)
	server := http.Server{
		Addr:    ":80",
		Handler: m,
	}

	server.ListenAndServe()
}
