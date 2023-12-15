package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func processString(s string, ch chan int) {
	current := 0
	for _, c := range s {
		current += int(c)
		current *= 17
		current %= 256
	}
	ch <- current
}

func main() {
	file, _ := os.Open("input")
	reader := bufio.NewReader(file)
	ch := make(chan int)
	nAwait := 0
	line, _ := reader.ReadString('\n')
	for line != "" {
		spl := strings.Split(strings.Trim(line, "\n"), ",")
		for _, s := range spl {
			go processString(s, ch)
			nAwait++
		}
		line, _ = reader.ReadString('\n')
	}
	part1 := 0
	for nAwait > 0 {
		part1 += <-ch
		nAwait--
	}
	fmt.Println("Part 1: ", part1)
}
