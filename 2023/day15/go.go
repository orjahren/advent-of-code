package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func getHash(s string) int {
	current := 0
	for _, c := range s {
		current += int(c)
		current *= 17
		current %= 256
	}
	return current
}

type Node struct {
	value int
	label string
	hash  int
}

func part1Hash(s string, part1Ch chan int) {
	part1Ch <- getHash(s)
}

func main() {
	file, _ := os.Open("input")
	reader := bufio.NewReader(file)
	part1Ch := make(chan int)
	line, _ := reader.ReadString('\n')
	part2Map := make([][]*Node, 256)
	nodeMap := make(map[string]Node)
	nAwaitPart1 := 0
	for line != "" {
		spl := strings.Split(strings.Trim(line, "\n"), ",")
		for _, s := range spl {
			go part1Hash(s, part1Ch)
			nAwaitPart1++
			if len(s) > 1 {
				// BEGIN part 2
				hasDash := strings.Contains(s, "-")
				var spl []string
				if hasDash {
					spl = strings.Split(s, "-")
					label := spl[0]
					hh := getHash(label)
					for i, n := range part2Map[hh] {
						if n.label == label {
							part2Map[hh] = append(part2Map[hh][:i], part2Map[hh][i+1:]...)
							break
						}
					}
				} else {
					spl = strings.Split(s, "=")
					label := spl[0]
					val, _ := strconv.Atoi(spl[1])
					hh := getHash(label)
					node := Node{val, label, hh}
					nodeMap[label] = node
					madeChange := false
					for i, n := range part2Map[hh] {
						if n.label == label {
							part2Map[hh][i].value = val
							madeChange = true
							break
						}
					}
					if !madeChange {
						part2Map[hh] = append(part2Map[hh], &node)
					}
				}
				// END part 2
			}
		}
		line, _ = reader.ReadString('\n')
	}
	part1Res := make(chan int)
	go (func() {
		locPart1Res := 0
		for nAwaitPart1 > 0 {
			locPart1Res += <-part1Ch
			nAwaitPart1--
		}
		part1Res <- locPart1Res
	})()

	part2Res := make(chan int)
	go (func() {
		locPart2Res := 0
		for _, arr := range part2Map {
			for slotInList, node := range arr {
				locPart2Res += ((node.hash + 1) * (slotInList + 1) * node.value)
			}
		}
		part2Res <- locPart2Res

	})()
	fmt.Println("Part 1: ", <-part1Res)
	fmt.Println("Part 2: ", <-part2Res)
}
