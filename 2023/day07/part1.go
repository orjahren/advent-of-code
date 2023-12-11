package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func handle(err error) {
	if err != nil {
		panic(err)
	}
}

func parseHand(line string) Hand {
	spl := strings.Split(line, " ")
	hand := Hand{}
	hand.bid, _ = strconv.Atoi(spl[1])
	for _, sym := range spl[0] {
		hand.symbols = append(hand.symbols, rune(sym))
	}
	return hand
}

type Hand struct {
	symbols []rune
	bid     int
}

func main() {
	//file, err := os.Open("input")
	file, err := os.Open("example")
	handle(err)
	defer file.Close()
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')
	hands := make([]Hand, 0)
	for line != "" {
		stripped := strings.TrimSpace(line)
		fmt.Println(stripped)
		hands = append(hands, parseHand(stripped))
		line, _ = reader.ReadString('\n')
	}
	fmt.Println(hands)
}
