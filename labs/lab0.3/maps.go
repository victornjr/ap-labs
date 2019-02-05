package main

//you can run it at https://play.golang.org/p/G5GaM6o0jBD
import (
	"strings"

	"golang.org/x/tour/wc"
)

func WordCount(s string) map[string]int {
	m := make(map[string]int)

	stringArray := strings.Fields(s)

	for _, element := range stringArray {
		m[element]++
	}

	return m
}

func main() {
	wc.Test(WordCount)
}
