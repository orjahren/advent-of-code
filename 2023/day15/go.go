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
	value, hash int
	label       string
}

func part1Hash(s string, part1Ch chan int) {
	part1Ch <- getHash(s)
}

func main() {
	file, _ := os.Open("input")
	reader := bufio.NewReader(file)

	part1Ch := make(chan int)
	nAwaitPart1 := 0

	part2Map := make([][]*Node, 256)
	nodeMap := make(map[string]*Node)

	line, _ := reader.ReadString('\n')
	for line != "" {
		for _, s := range strings.Split(strings.Trim(line, "\n"), ",") {
			if len(s) > 1 {
				go part1Hash(s, part1Ch)
				nAwaitPart1++
				if strings.Contains(s, "-") {
					spl := strings.Split(s, "-")
					label := spl[0]
					hh := getHash(label)
					newSlice := make([]*Node, 0)
					for _, n := range part2Map[hh] {
						if n.label != label {
							newSlice = append(newSlice, n)
						}
					}
					part2Map[hh] = newSlice
					delete(nodeMap, label)
				} else {
					spl := strings.Split(s, "=")
					label := spl[0]
					val, _ := strconv.Atoi(spl[1])
					if other, nodeWithLabelExists := nodeMap[label]; nodeWithLabelExists {
						other.value = val
					} else {
						node := Node{val, getHash(label), label}
						part2Map[node.hash] = append(part2Map[node.hash], &node)
						nodeMap[label] = &node
					}
				}
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
