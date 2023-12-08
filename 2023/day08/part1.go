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

type Node struct {
	name        string
	left        *Node
	right       *Node
	nameOfLeft  string
	nameOfRight string
}

func readFileAndStructureInput(reader bufio.Reader) ([]*Node, map[string]*Node, []Node) {
	nodes := make([]*Node, 0)
	nodesRaw := make([]Node, 0)
	nameToNodeMap := make(map[string]*Node)

	onlyLettersRegex := regexp.MustCompile("[a-zA-Z]+")
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		spl := strings.Split(line, " ")
		if len(spl) > 1 {
			var node Node
			letters := onlyLettersRegex.FindAllString(line, -1)
			node.name = letters[0]
			node.nameOfLeft = letters[1]
			node.nameOfRight = letters[2]
			nodesRaw = append(nodesRaw, node)
			nodes = append(nodes, &node)
			nameToNodeMap[node.name] = &node
		}
	}
	for i := range nodes {
		node := nodes[i]
		node.left = nameToNodeMap[node.nameOfLeft]
		node.right = nameToNodeMap[node.nameOfRight]
	}
	return nodes, nameToNodeMap, nodesRaw
}

func main() {
	file, _ := os.Open("input")
	reader := bufio.NewReader(file)

	instructions, _ := reader.ReadString('\n')
	instructions = strings.TrimSuffix(instructions, "\n")

	_, nameToNodeMap, _ := readFileAndStructureInput(*reader)

	instructionCounter := 0
	currentNode := nameToNodeMap["AAA"]
	for currentNode.name != "ZZZ" {
		instruction := getInstruction(instructionCounter, instructions)
		if instruction == 'L' {
			currentNode = currentNode.left
		} else {
			currentNode = currentNode.right
		}
		instructionCounter++
	}
	fmt.Println("Part 1: ", instructionCounter)
}
