package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func part1Hash(s string, part1Ch chan int) {
	current := 0
	for _, c := range s {
		current += int(c)
		current *= 17
		current %= 256
	}
	part1Ch <- current
}

func main() {
	file, _ := os.Open("input")
	reader := bufio.NewReader(file)
	part1Ch := make(chan int)
	nAwait := 0
	line, _ := reader.ReadString('\n')
	for line != "" {
		spl := strings.Split(strings.Trim(line, "\n"), ",")
		for _, s := range spl {
			go part1Hash(s, part1Ch)
			nAwait++
		}
		line, _ = reader.ReadString('\n')
	}
	part1Res := 0
	for nAwait > 0 {
		part1Res += <-part1Ch
		nAwait--
	}
	fmt.Println("Part 1: ", part1Res)
}
