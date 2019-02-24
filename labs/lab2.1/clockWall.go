package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
	"time"
)

type Clock struct {
	city, hostPort string
}

func (clock *Clock) getHour(reader io.Reader, writer io.Writer) {
	scanner := bufio.NewScanner(reader)
	for scanner.Scan() {
		fmt.Fprintf(writer, "%s: %s\n", clock.city, scanner.Text())
	}

	if scanner.Err() != nil {
		log.Printf("There's an error with %s: %s", clock.city, scanner.Err())
	}
}

func main() {
	if len(os.Args) <= 1 {
		fmt.Fprintln(os.Stderr, "Usage: ./clockWall City=localhost:# [...]")
		os.Exit(1)
	}

	clocks := make([]*Clock, 0)
	inputCities := os.Args[1:]

	for _, input := range inputCities {
		completeInput := strings.Split(input, "=")
		if len(completeInput) != 2 {
			fmt.Fprintf(os.Stderr, "The argument is wrong (please use as marked on usage) %s\n", input)
			os.Exit(1)
		}
		clocks = append(clocks, &Clock{completeInput[0], completeInput[1]})
	}

	for _, clk := range clocks {
		userInput, _ := net.Dial("tcp", clk.hostPort)

		defer userInput.Close()
		go clk.getHour(userInput, os.Stdout)
	}

	for {
		time.Sleep(time.Minute)
	}
}
