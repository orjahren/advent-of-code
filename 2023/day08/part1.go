package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strings"
)

func getInstruction(idx int, instructions string) rune {
	return rune(instructions[idx%len(instructions)])
}

func calculatePathFromLine(lineNumber int, lines []string, ch chan int) {}

type Node struct {
	name        string
	left        *Node
	right       *Node
	nameOfLeft  string
	nameOfRight string
}

func main() {
	//file, _ := os.Open("input")
	file, _ := os.Open("example")
	reader := bufio.NewReader(file)

	instructions, _ := reader.ReadString('\n')
	fmt.Println(instructions)
	reader.ReadString('\n')

	lines := make([]string, 0)
	nodes := make([]Node, 0)
	nameToNodeMap := make(map[string]*Node)

	onlyLettersRegex := regexp.MustCompile("[a-zA-Z]+")

	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		lines = append(lines, line)
		fmt.Println("Spl: ")
		spl := strings.Split(line, " ")
		fmt.Println(len(spl))
		if len(spl) > 1 {

			var node Node
			fmt.Println(spl)
			for i, s := range spl {
				fmt.Println(i, ": "+s)
			}
			node.name = spl[0]
			node.nameOfLeft = onlyLettersRegex.FindString(spl[2])
			node.nameOfRight = onlyLettersRegex.FindString(spl[3])
			fmt.Println(node)
			nodes = append(nodes, node)
			nameToNodeMap[node.name] = &node
		}
	}
	fmt.Println(nodes)
	fmt.Println(nameToNodeMap)
	fmt.Println("\t Har laget alle noder")
	fmt.Println("\t Setter opp pekere")
	for i, node := range nodes {
		node.left = nameToNodeMap[node.nameOfLeft]
		node.right = nameToNodeMap[node.nameOfRight]
		nodes[i] = node
	}
	fmt.Println("\t Har satt opp pekere")
	fmt.Println(nodes)
	fmt.Println(nameToNodeMap)
}
