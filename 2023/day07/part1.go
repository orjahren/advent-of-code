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
	hand.bid, _ = strconv.Atoi(spl[0])
	for _, sym := range spl[1] {
		hand.symnols = append(hand.symnols, rune(sym))
	}
	return hand
}

type Hand struct {
	symnols []rune
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
		hands = append(hands, parseHand(stripped))
		fmt.Println(stripped)
		line, _ = reader.ReadString('\n')
	}
	fmt.Println(hands)
}
