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
}

func part1Hash(s string, part1Ch chan int) {
	part1Ch <- getHash(s)
}

func main() {
	file, _ := os.Open("input")
	//file, _ := os.Open("example")
	reader := bufio.NewReader(file)
	part1Ch := make(chan int)
	nAwait := 0
	line, _ := reader.ReadString('\n')
	part2Map := make([][]*Node, 256)
	nodeMap := make(map[string]Node)
	for line != "" {
		spl := strings.Split(strings.Trim(line, "\n"), ",")
		for _, s := range spl {
			go part1Hash(s, part1Ch)
			nAwait++

			if len(s) > 1 {
				// BEGIN part 2
				fmt.Println("s:", s)
				hasDash := strings.Contains(s, "-")
				var spl []string
				if hasDash {
					spl = strings.Split(s, "-")
					label := spl[0]

					//node := nodeMap[label]
					hh := getHash(label)
					// Remove item from list
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
					node := Node{val, label}
					nodeMap[label] = node
					madeChange := false
					// If node exists, replace value
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
				fmt.Println("spl:", spl)
				// END part 2

			}
		}
		line, _ = reader.ReadString('\n')
	}
	part1Res := 0
	for nAwait > 0 {
		part1Res += <-part1Ch
		nAwait--
	}
	part2Res := 0
	for k, v := range part2Map {
		fmt.Println(k, v)
		slotInList := 0
		for _, e := range v {
			fmt.Println(e)
			node := e

			hh := getHash(node.label) + 1
			slotInList++

			fmt.Printf("hh: %v, slotInList: %v, node.value: %v, node.label: %v\n", hh, slotInList, node.value, node.label)
			fmt.Println("Result:", hh*slotInList*node.value)

			part2Res += (hh * slotInList * node.value)
		}
	}

	fmt.Println("Part 1: ", part1Res)
	fmt.Println("Part 2: ", part2Res)
}
