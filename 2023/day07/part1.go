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
func sliceContains4Twos(arr []int) bool {
	count := 0
	for _, val := range arr {
		if val == 2 {
			count++
		}
	}
	return count == 4
}
func classifyHand(hand Hand) int {
	/*
			Every hand is exactly one type. From strongest to weakest, they are:

		Five of a
		kind, where all five cards have the same label: AAAAA
		Four of a kind, where four cards have the same label and one card has a different label: AA8AA
		Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
		Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
		Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
		One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
		High card, where all cards' labels are distinct: 23456
		Hands are primarily ordered based on type; for example, every full house is stronger than any three of a kind.
	*/

	rewrite_map := map[rune]rune{
		'T': 'A',
		'J': 'B',
		'Q': 'C',
		'K': 'D',
		'A': 'E',
	}

	for i, sym := range hand.symbols {
		if sym == 'T' || sym == 'J' || sym == 'Q' || sym == 'K' || sym == 'A' {
			hand.symbols[i] = rewrite_map[sym]
		}
	}
	//hand.symbols = slices.SortRunes(hand.symbols)

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
	if sliceContains4Twos(countsArr) {
		return 2
	}
	if slices.Contains(countsArr, 2) {
		return 1
	}
	return 0

}

func sortHandsByHighCard(hands []Hand) []Hand {
	// sort by high card
	for i := 0; i < len(hands); i++ {
		for j := 0; j < len(hands)-1; j++ {
			if hands[j].symbols[0] < hands[j+1].symbols[0] {
				hands[j], hands[j+1] = hands[j+1], hands[j]
			}
		}
	}
	return hands
}

func sortHandsByRank(hands []Hand) []Hand {
	/*
			Every hand is exactly one type. From strongest to weakest, they are:

		Five of a kind, where all five cards have the same label: AAAAA
		Four of a kind, where four cards have the same label and one card has a different label: AA8AA
		Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
		Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
		Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
		One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
		High card, where all cards' labels are distinct: 23456
		Hands are primarily ordered based on type; for example, every full house is stronger than any three of a kind.
	*/

	// sort by rank
	// 5 of a kind
	// 4 of a kind
	// full house
	// 3 of a kind
	// 2 pair
	// 1 pair
	// high card

	handsByRank := make([][]Hand, 6)
	for _, hand := range hands {
		rank := classifyHand(hand)
		handsByRank[rank] = append(handsByRank[rank], hand)
	}
	for i := 0; i < len(handsByRank); i++ {
		handsByRank[i] = sortHandsByHighCard(handsByRank[i])
	}
	ret := make([]Hand, 0)
	for i := 0; i < len(handsByRank); i++ {
		ret = append(ret, handsByRank[i]...)
	}

	return ret
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
	sorted := sortHandsByRank(hands)
	fmt.Println(sorted)

	values := make([]int, 0)
	bids := make([]int, 0)
	for i, hand := range sorted {
		values = append(values, (i+1)*hand.bid)
		bids = append(bids, hand.bid)
	}
	fmt.Println(values)
	part1 := 0
	for _, val := range values {
		part1 += val
	}
	fmt.Println("Part 1:", part1)
	fmt.Println("Bids:", bids)

}
