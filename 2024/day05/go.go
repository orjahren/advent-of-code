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
	fmt.Println(spl)

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
		println(text)
		p := lineToPair(stripped, id)
		id++
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

func updateIsLegalUnderRule(update Update, rule Rule, ruleCh chan bool) {
	idxX := slices.Index(update, rule.x)
	idxY := slices.Index(update, rule.y)
	fmt.Println("Verifiserer gyldighet av", rule, "på", update, ", Indeces er:", idxX, idxY)

	hasBoth := idxX != -1 && idxY != -1

	if hasBoth {
		isLegal := idxX < idxY

		if isLegal {
			ruleCh <- true
			return
		}
	}

	ruleCh <- false
}
func updateIsLegalUnderRuleSEQ(update Update, rule Rule) bool {
	idxX := slices.Index(update, rule.x)
	idxY := slices.Index(update, rule.y)
	fmt.Println("Verifiserer gyldighet av", rule, "på", update, ", Indeces er:", idxX, idxY)

	hasBoth := idxX != -1 && idxY != -1

	if hasBoth {
		isLegal := idxX < idxY

		if isLegal {
			println("LOV")
			return true
		} else {

			println("IKKE lov")
			return false
		}
	}

	return true
}

func getUpdateIfLegal(update Update, rules []Rule, retCh chan Update) {
	for _, rule := range rules {
		if !updateIsLegalUnderRuleSEQ(update, rule) {
			retCh <- nil
			return
		}
	}
	retCh <- update
	if false {
		ruleCh := make(chan bool)
		for _, rule := range rules {
			go updateIsLegalUnderRule(update, rule, ruleCh)
		}
		for range rules {
			tv := <-ruleCh
			if !tv {
				retCh <- nil
				return
			}
		}
		// If not retrned above^, this update must be legal
		retCh <- update
	}
}

func getMiddleValueOfUpdate(u Update) int {
	mid := len(u) / 2
	return u[mid]
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	rules := readRules(scanner)
	println("Read", len(rules), "rules")
	updates := readUpdates(scanner)
	println("Read", len(updates), "updates")
	updateCh := make(chan Update)
	for _, u := range updates {
		go getUpdateIfLegal(u, rules, updateCh)
	}
	legalUpdates := make([]Update, 0)
	for range updates {
		u := <-updateCh
		if u != nil {
			legalUpdates = append(legalUpdates, u)
		}
	}
	res := 0
	for _, u := range legalUpdates {
		mid := getMiddleValueOfUpdate(u)
		fmt.Println("Mid value:", mid)
		res += mid

	}
	println("Har", len(legalUpdates), "lovlige updates")
	println(("De er:"))
	fmt.Println(legalUpdates)
	fmt.Println("Part 1:", res)

}
