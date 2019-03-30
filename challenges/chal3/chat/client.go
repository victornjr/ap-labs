// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 227.

// Netcat is a simple read/write client for TCP servers.
package main

import (
	"io"
	"log"
	"net"
	"os"
	"flag"
	"fmt"
)

//!+
var userName string
var serverName string
func main() {
	flag.StringVar(&userName,"user","defaultUser","for naming the user")
	flag.StringVar(&serverName,"server","localhost:8000","for getting server")
	flag.Parse()

	conn, err := net.Dial("tcp", serverName)
	if err != nil {
		log.Fatal(err)
	}

	done := make(chan struct{})
	go func() {
		io.Copy(os.Stdout, conn) // NOTE: ignoring errors
		log.Println("done")
		done <- struct{}{} // signal the main goroutine
	}()

	fmt.Fprintf(conn,userName + " ")
	mustCopy(conn, os.Stdin)
	conn.Close()
	<-done // wait for background goroutine to finish
}

//!-

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst,src); err != nil {
		log.Fatal(err)
	}
}
