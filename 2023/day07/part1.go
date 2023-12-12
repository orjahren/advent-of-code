package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
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

func classifyHand(hand Hand) int {
	countsMap := make(map[rune]int)
	for _, sym := range hand.symbols {
		countsMap[sym]++
	}
	countsArr := make([]int, 0)
	for _, sym := range hand.symbols {
		countsArr = append(countsArr, countsMap[sym])
	}

	if slices.Contains(countsArr, 5) {
		return 6
	}
	if slices.Contains(countsArr, 4) {
		return 5
	}
	if slices.Contains(countsArr, 3) {
		if slices.Contains(countsArr, 2) {
			return 4
		}
		return 3
	}
	if (func() bool {
		count := 0
		for _, val := range countsArr {
			if val == 2 {
				count++
			}
		}
		return count == 4
	})() {
		return 2
	}
	if slices.Contains(countsArr, 2) {
		return 1
	}
	return 0

}

func sortHandsByRank(hands []Hand) []Hand {
	rewrite_map := map[rune]rune{
		'T': 'A',
		'J': 'B',
		'Q': 'C',
		'K': 'D',
		'A': 'E',
	}
	handsByRank := make([][]Hand, 7)
	for _, hand := range hands {
		for i, sym := range hand.symbols {
			if rewrite_map[sym] != 0 {
				hand.symbols[i] = rewrite_map[sym]
			}
		}
		rank := classifyHand(hand)
		handsByRank[rank] = append(handsByRank[rank], hand)
	}
	ret := make([]Hand, 0)
	for i := 0; i < len(handsByRank); i++ {
		slices.SortStableFunc(handsByRank[i], (func(a, b Hand) int {
			for i := 0; i < len(a.symbols); i++ {
				if a.symbols[i] < b.symbols[i] {
					return -1
				} else if a.symbols[i] > b.symbols[i] {
					return 1
				}
			}
			return 0
		}))
		ret = append(ret, handsByRank[i]...)
	}
	return ret
}

type Hand struct {
	symbols []rune
	bid     int
}

func main() {
	file, err := os.Open("input")
	handle(err)
	defer file.Close()
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')
	hands := make([]Hand, 0)
	for line != "" {
		stripped := strings.TrimSpace(line)
		hands = append(hands, parseHand(stripped))
		line, _ = reader.ReadString('\n')
	}
	sorted := sortHandsByRank(hands)
	part1 := 0
	for i, hand := range sorted {
		part1 += (i + 1) * hand.bid
	}
	fmt.Println("Part 1:", part1)
}
