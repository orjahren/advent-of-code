package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Rule struct {
	x, y int
}

type Update = []int

func lineToPair(line string) Rule {
	spl := strings.Split(line, "|")
	fmt.Println(spl)

	a, _ := strconv.Atoi(spl[0])
	b, _ := strconv.Atoi(spl[1])

	return Rule{a, b}
}

func readRules(scanner *bufio.Scanner) []Rule {
	pairs := make([]Rule, 0)
	for scanner.Scan() {
		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		if len(stripped) == 0 {
			return pairs
		}
		println(text)
		p := lineToPair(stripped)
		fmt.Println(p)
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
		println(text)
		// var u Update = nil
		u := lineToUpdate(stripped)
		fmt.Println(u)
		updates = append(updates, u)
	}
	return updates
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	rules := readRules(scanner)
	println("Read", len(rules), "rules")
	updates := readUpdates(scanner)
	println("Read", len(updates), "updates")

}
