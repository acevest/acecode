/*
 * ------------------------------------------------------------------------
 *   File Name: logger.go
 *      Author: Zhao Yanbai
 *              2018-12-11 16:55:07 星期二 CST
 * Description: none
 * ------------------------------------------------------------------------
 */
package main

import (
	"fmt"
	"io"
	"log"
	"os"
)

var logger *log.Logger
var logfile *os.File

func init() {
	logfile, err := os.OpenFile("./log.txt", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0666)
	if err != nil {
		log.Fatal(err)
	}

	logger = log.New(logfile, "LogPrefix ", log.Ldate|log.Lmicroseconds|log.Lshortfile)
	logger.Println("hello log file")

	logger.SetOutput(io.MultiWriter(os.Stdout, logfile))
	logger.Println("hello stdout & log file multi writer")

	logger.SetOutput(io.Writer(logfile))
	logger.Println("hello log file writer")
}

func TryLogger() {
	logger.Println("test log")
}

func main() {
	defer func() {
		logfile.Sync()
		logfile.Close()
	}()

	defer fmt.Println("Program Exited...")

	TryLogger()

}
