package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
	"strconv"
	"strings"
)

type Rule struct {
	x, y, id int
}

type Update = []int

func lineToPair(line string, id int) Rule {
	spl := strings.Split(line, "|")
	a, _ := strconv.Atoi(spl[0])
	b, _ := strconv.Atoi(spl[1])
	return Rule{a, b, id}
}

func readRules(scanner *bufio.Scanner) []Rule {
	pairs := make([]Rule, 0)
	id := 0
	for scanner.Scan() {
		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		if len(stripped) == 0 {
			return pairs
		}
		p := lineToPair(stripped, id)
		id++
		pairs = append(pairs, p)

	}
	return pairs
}

func lineToUpdate(line string) Update {
	spl := strings.Split(line, ",")
	arr := make(Update, len(spl))
	for i := range arr {
		arr[i], _ = strconv.Atoi(spl[i])
	}
	return arr
}

func readUpdates(scanner *bufio.Scanner) []Update {
	updates := make([]Update, 0)
	for scanner.Scan() {
		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		if len(stripped) == 0 {
			return updates
		}
		u := lineToUpdate(stripped)
		updates = append(updates, u)
	}
	return updates
}

func updateIsLegalUnderRule(update Update, rule Rule, ruleCh chan bool) {
	idxX := slices.Index(update, rule.x)
	idxY := slices.Index(update, rule.y)

	hasBoth := idxX != -1 && idxY != -1

	if hasBoth {
		isLegal := idxX < idxY
		ruleCh <- isLegal
		return
	}

	ruleCh <- true
}

func getUpdateIfLegalP1(update Update, rules []Rule, p1Ch chan Update) {
	ruleCh := make(chan bool)
	defer close(ruleCh)

	for _, rule := range rules {
		go updateIsLegalUnderRule(update, rule, ruleCh)
	}

	isLegal := true
	for range rules {
		tv := <-ruleCh
		if !tv {
			isLegal = false
		}
	}

	if isLegal {
		p1Ch <- update
	} else {
		p1Ch <- nil
	}
}
func getUpdateIfIllegal(update Update, rules []Rule, p2Ch chan Update) {
	ruleCh := make(chan bool)
	defer close(ruleCh)

	for _, rule := range rules {
		go updateIsLegalUnderRule(update, rule, ruleCh)
	}

	isLegal := true
	for range rules {
		tv := <-ruleCh
		if !tv {
			isLegal = false
		}
	}

	if !isLegal {
		p2Ch <- update
	} else {
		p2Ch <- nil
	}
}

func getMiddleValueOfUpdate(u Update) int {
	mid := len(u) / 2
	return u[mid]
}

// permute generates all permutations of the input array
func permute(arr Update) []Update {
	var result [][]int
	generatePermutations(arr, 0, &result)
	return result
}

// generatePermutations is a helper function to generate permutations using backtracking
func generatePermutations(arr Update, start int, result *[]Update) {
	if start == len(arr)-1 {
		// Make a copy of arr to avoid modification in future permutations
		permutation := make([]int, len(arr))
		copy(permutation, arr)
		*result = append(*result, permutation)
		return
	}

	for i := start; i < len(arr); i++ {
		// Swap element at start with element at i
		arr[start], arr[i] = arr[i], arr[start]
		// Recurse on the remaining elements
		generatePermutations(arr, start+1, result)
		// Swap back to restore the original array
		arr[start], arr[i] = arr[i], arr[start]
	}
}

func part2(rules []Rule, updates []Update) int {

	illegalUpdates := make([]Update, 0)

	// Extract all illegal updates (TODO: Burde gjøres som en del av part1)
	illegalUpdatesCh := make(chan Update)
	for _, baseUpdate := range updates {
		go getUpdateIfIllegal(baseUpdate, rules, illegalUpdatesCh)
	}
	for range updates {
		v := <-illegalUpdatesCh
		if v != nil {
			illegalUpdates = append(illegalUpdates, v)
		}
	}

	exp := 0
	bruteForcedCh := make(chan Update)
	for _, baseUpdate := range illegalUpdates {
		for _, perm := range permute(baseUpdate) {
			exp++
			go getUpdateIfLegalP1(perm, rules, bruteForcedCh)

		}
	}
	p2 := 0
	for range exp {
		v := <-bruteForcedCh
		if v != nil {
			mid := getMiddleValueOfUpdate(v)
			p2 += mid
		}
	}

	return p2
}

func part1(rules []Rule, updates []Update) int {
	p1Ch := make(chan Update, len(updates))

	for _, u := range updates {
		go getUpdateIfLegalP1(u, rules, p1Ch)
	}

	legalUpdates := make([]Update, 0)
	for range updates {
		u := <-p1Ch
		if u != nil {
			legalUpdates = append(legalUpdates, u)
		}
	}

	p1 := 0
	for _, u := range legalUpdates {
		mid := getMiddleValueOfUpdate(u)
		p1 += mid
	}
	return p1
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	rules := readRules(scanner)
	println("Read", len(rules), "rules")
	updates := readUpdates(scanner)
	println("Read", len(updates), "updates")

	p1 := part1(rules, updates)
	fmt.Println("Part 1:", p1)

	p2 := part2(rules, updates)
	fmt.Println("Part 2:", p2)
}
