/*
 * ------------------------------------------------------------------------
 *   File Name: port_forward.go
 *      Author: Zhao Yanbai
 *              2019-03-27 22:53:06 星期三 CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"flag"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	//	"sync"
)

var logDebug *log.Logger
var logInfo *log.Logger
var logImpt *log.Logger
var logErr *log.Logger

func CreateLogger(path string) error {
	logfile, err := os.OpenFile(path, os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0666)
	if err != nil {
		fmt.Printf("failed open log file: %s\n", path)
		return err
	}

	logDebug = log.New(logfile, "[DEBUG]", log.Ldate|log.Lmicroseconds|log.Lshortfile)
	logInfo = log.New(logfile, "[INFO]", log.Ldate|log.Lmicroseconds|log.Lshortfile)
	logImpt = log.New(logfile, "[IMPT]", log.Ldate|log.Lmicroseconds|log.Lshortfile)
	logErr = log.New(logfile, "[ERROR]", log.Ldate|log.Lmicroseconds|log.Lshortfile)

	logDebug.SetOutput(io.Writer(logfile))
	//logInfo.SetOutput(io.Writer(logfile))
	logInfo.SetOutput(io.MultiWriter(os.Stdout, logfile))
	logImpt.SetOutput(io.MultiWriter(os.Stdout, logfile))
	logErr.SetOutput(io.MultiWriter(os.Stderr, logfile))

	return nil
}

func main() {

	var local string
	var remote string
	var logPath string
	flag.StringVar(&local, "local", "localhost:80", "local addr <ip:port>")
	flag.StringVar(&remote, "remote", "localhost:8080", "remote addr <ip:port>")
	flag.StringVar(&logPath, "log", "./port_forward.log", "log file path")
	flag.Parse()

	err := CreateLogger(logPath)
	if err != nil {
		log.Fatal("failed create logger")
	}

	defer logInfo.Println("Program Exited...")

	logImpt.Printf("forward from %s to %s\n", local, remote)

	listener, err := net.Listen("tcp", local)
	if err != nil {
		logErr.Println(err)
		return
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			logErr.Println(err)
			continue
		}

		logInfo.Printf("new connection from %s\n", conn.RemoteAddr())

		go handleNewConn(conn, remote)
	}
}

func handleNewConn(cli_conn net.Conn, remote string) {
	defer cli_conn.Close()

	svr_conn, err := net.Dial("tcp", remote)
	if err != nil {
		logErr.Println(err)
		return
	}

	defer svr_conn.Close()

	//var wg sync.WaitGroup
	//wg.Add(2)
	end := make(chan bool)

	go func() {
		io.Copy(cli_conn, svr_conn)
		//wg.Done()
		end <- true
	}()

	go func() {
		io.Copy(svr_conn, cli_conn)
		//wg.Done()
		end <- true
	}()

	<-end
	//wg.Wait()

	logInfo.Printf("connection from %s closed\n", cli_conn.RemoteAddr())
}
