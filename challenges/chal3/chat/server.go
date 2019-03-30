// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 254.
//!+

// Chat is a server that lets clients chat with each other.
package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"flag"
	"time"
	"strings"
)

//!+broadcaster
type client chan<- string // an outgoing message channel

type userInfo struct {
    UserIP string
    UserChannel  chan<-string
}

var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) // all incoming client messages
)

func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		case msg := <-messages:
			// Broadcast incoming message to all
			// clients' outgoing message channels.
			for cli := range clients {
				cli <- msg
			}

		case cli := <-entering:
			clients[cli] = true

		case cli := <-leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

var timeZone = "America/Mexico_City"
func getTime() string{
	loc, _ := time.LoadLocation(timeZone)
	t := time.Now().In(loc)
	return t.Format("15:04:05\n")
}
//!-broadcaster

//!+handleConn
var allClients = make(map[string]userInfo);
//var user1 = userInfo{"hola",make(chan string)}//make(chan string)
func handleConn(conn net.Conn) {
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)

	ipAddress := fmt.Sprintf(":%d",portNumber)
	who := strings.TrimSuffix(conn.LocalAddr().String(), ipAddress)
	//fmt.Println(who)
	nameU,_:= bufio.NewReader(conn).ReadString(' ')
	fmt.Println(serverName,"New connected user [",nameU,"]")
	ch <- serverName + "Welcome to the Simple IRC Server"
	ch <- serverName + "Your user [" + nameU + "] is successfully logged"
	messages <- serverName + "New connected user [" + nameU + "]"

	/*if(nameU == "Victor "){
		user1.UserChannel = ch //assign channel to variable
	}*/
	entering <- ch
	//allClients = append(allClients,nameU)
	allClients[nameU] = userInfo{who,ch}
	input := bufio.NewScanner(conn)

	for input.Scan() {
		recievedValue := input.Text()
		splitedValue := strings.Split(recievedValue," ")
		if splitedValue[0] == "/users" {
			clientsList := serverName
			for key,_ := range allClients{
				clientsList += key + ", "
			}
			/*for i:=0;i<len(allClients);i++{
				clientsList += allClients[i] + ", "
			}*/
			ch <- clientsList
		}else if splitedValue[0] == "/time"{
			ch <- serverName + "Local Time: " + timeZone + " " + getTime()
		}else if splitedValue[0] == "/user" {
			if len(splitedValue) == 2{
				wantedClient,ok := allClients[splitedValue[1] + " "]
				if ok {
					ch <- serverName + "username: " + splitedValue[1] + ", IP: " + wantedClient.UserIP
				}else{
					ch <- serverName + "The user [" + splitedValue[1] + "] doesn't exist or is not connected."
				}
				 //wantedClient.UserChannel <- "hola" //for sending to an especific channel
			}else{
				ch <- serverName + "Please use the /user command correctly (/user username)."
			}
			//user1.UserChannel <- "hola" //sends that mesage to that user
		}else if splitedValue[0] == "/msg"{
			if len(splitedValue) > 3{
				wantedClient,ok := allClients[splitedValue[1] + " "]
				if ok {
					wantedClient.UserChannel <- nameU + "(private)> " + strings.Join(splitedValue[2:]," ")
				}else{
					ch <- serverName + "The user [" + splitedValue[1] + "] doesn't exist or is not connected."
				}
			}else{
				ch <- serverName + "Please use the /msg command correctly (/msg username message)."
			}
		}else{
			messages <- nameU + "> " + recievedValue
		}
	}
	// NOTE: ignoring potential errors from input.Err()

	leaving <- ch
	messages <- serverName + "[" + nameU + "]" + "left"
	fmt.Println(serverName,"[",nameU,"]","left")
	delete(allClients,nameU)
	//allClients = removeFromArray(allClients,nameU)
	conn.Close()
}

func removeFromArray(array []string, elementDelete string) []string {
    for i, v := range array {
        if v == elementDelete {
            return append(array[:i], array[i+1:]...)
        }
    }
    return array
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

//!-handleConn

//!+main
var hostName string
var portNumber int
var serverName = "irc-server > "
func main() {
	flag.StringVar(&hostName,"host","localhost","for naming the host")
	flag.IntVar(&portNumber,"port",8000,"for getting host number")
	flag.Parse()
	//fmt.Println(hostName)
	//fmt.Println(portNumber)

	fmt.Println(serverName," Simple IRC Server started at ",hostName,":",portNumber)
	fmt.Println(serverName,"Ready for receiving new clients")

	serverValue := fmt.Sprintf("%s:%d",hostName, portNumber)

	listener, err := net.Listen("tcp", serverValue)
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

//!-main
