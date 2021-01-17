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
	frameChan = make(chan []byte, 128)
}


func audioHandler(w http.ResponseWriter, r *http.Request) {
	var err error
	var ws *websocket.Conn

	log.Printf("audio\n")
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

            err = ws.WriteMessage(websocket.BinaryMessage, []byte{'1'})
            if err != nil {
                log.Printf("write to arduino error: %v", err)
                //break
            }
		default:
			log.Printf("drop frame")
		}

	}
}

func streamHandler(w http.ResponseWriter, r *http.Request) {
	var err error
	var ws *websocket.Conn

	log.Printf("stream\n")

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
        //case <-time.After(1 * time.Millisecond):
        default:
            time.Sleep(10 * time.Millisecond)
			continue
		}

		err = ws.WriteMessage(websocket.BinaryMessage, data)
		if err != nil {
			break
		}
	}
}

func playerHandler(w http.ResponseWriter, r *http.Request) {
	tmpl := template.Must(template.ParseFiles("./player.html"))
	var data = map[string]interface{}{}
	tmpl.Execute(w, data)
}

func main() {
	defer fmt.Println("Program Exited...")

	m := http.NewServeMux()
	m.HandleFunc("/audio", audioHandler)
	m.HandleFunc("/player", playerHandler)
	m.HandleFunc("/stream", streamHandler)
	server := http.Server{
		Addr:    ":80",
		Handler: m,
	}

	server.ListenAndServe()
}
