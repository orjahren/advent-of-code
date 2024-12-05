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
type Pair struct {
	legal, illegal Update
}

func lineToRule(line string, id int) Rule {
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
		p := lineToRule(stripped, id)
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

func updateIsLegalUnderRule(update Update, rule Rule) bool {
	idxX := slices.Index(update, rule.x)
	idxY := slices.Index(update, rule.y)

	hasBoth := idxX != -1 && idxY != -1

	if hasBoth {
		isLegal := idxX < idxY
		return isLegal
	}

	return true
}
func getMiddleValueOfUpdate(u Update) int {
	mid := len(u) / 2
	return u[mid]
}

func getLegality(update Update, rules []Rule) bool {
	ruleCh := make(chan bool)
	for _, rule := range rules {
		go func() {
			ruleCh <- updateIsLegalUnderRule(update, rule)
		}()
	}
	for range rules {
		if !<-ruleCh {
			return false
		}
	}
	return true
}

// https://github.com/LinuxFanboy/advent-of-code/blob/main/aoc_2024/Day_05/solution.go
func correctOrder(update []int, rules []Rule) []int {
	graph, indegree := buildGraph(update, rules)
	queue, sorted := []int{}, []int{}

	for page, degree := range indegree {
		if degree == 0 {
			queue = append(queue, page)
		}
	}

	for len(queue) > 0 {
		cur := queue[0]
		queue = queue[1:]
		sorted = append(sorted, cur)
		for _, neighbor := range graph[cur] {
			if indegree[neighbor]--; indegree[neighbor] == 0 {
				queue = append(queue, neighbor)
			}
		}
	}
	return sorted
}

// https://github.com/LinuxFanboy/advent-of-code/blob/main/aoc_2024/Day_05/solution.go
func buildGraph(update []int, rules []Rule) (map[int][]int, map[int]int) {
	graph := make(map[int][]int)
	indegree := make(map[int]int)
	for _, page := range update {
		graph[page] = []int{}
		indegree[page] = 0
	}
	for _, rule := range rules {
		if slices.Contains(update, rule.x) && slices.Contains(update, rule.y) {
			graph[rule.x] = append(graph[rule.x], rule.y)
			indegree[rule.y]++
		}
	}
	return graph, indegree
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	rules := readRules(scanner)
	updates := readUpdates(scanner)

	ch := make(chan Pair)
	for _, update := range updates {
		go func() {
			isLegal := getLegality(update, rules)
			if isLegal {
				ch <- Pair{update, nil}
			} else {
				ch <- Pair{nil, update}
			}
		}()
	}

	println("Parsed", len(rules), "rules")
	println("Parsed", len(updates), "updates")

	defer close(ch)
	p2Ch := make(chan int)

	p1 := 0
	numIllegal := 0
	for range updates {
		u := <-ch
		if u.legal != nil {
			mid := getMiddleValueOfUpdate(u.legal)
			p1 += mid
		} else {
			numIllegal++
			go func() {
				v := correctOrder(u.illegal, rules)
				p2Ch <- getMiddleValueOfUpdate(v)
			}()
		}
	}

	fmt.Println("Part 1:", p1)
	p2 := 0
	for range numIllegal {
		p2 += <-p2Ch
	}
	fmt.Println("Part 2:", p2)
}
