package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strings"
)

type Node struct {
	name        string
	left        *Node
	right       *Node
	nameOfLeft  string
	nameOfRight string
}

func readFileAndStructureInput(reader *bufio.Reader) map[string]*Node {

	nameToNodeMap := make(map[string]*Node)
	onlyLettersRegex := regexp.MustCompile("[a-zA-Z]+")

	for {
		line, err := reader.ReadString('\n')
		spl := strings.Split(line, " ")
		if err != nil {
			break
		}
		if len(spl) > 1 {
			var node Node
			letters := onlyLettersRegex.FindAllString(line, -1)
			node.name = letters[0]
			node.nameOfLeft = letters[1]
			node.nameOfRight = letters[2]
			nameToNodeMap[node.name] = &node
		}
	}
	for i := range nameToNodeMap {
		node := nameToNodeMap[i]
		node.left = nameToNodeMap[node.nameOfLeft]
		node.right = nameToNodeMap[node.nameOfRight]
	}
	return nameToNodeMap
}

func main() {
	file, _ := os.Open("input")
	reader := bufio.NewReader(file)

	instructions, _ := reader.ReadString('\n')
	instructions = strings.TrimSuffix(instructions, "\n")

	nameToNodeMap := readFileAndStructureInput(reader)

	instructionCounter := 0
	currentNode := nameToNodeMap["AAA"]
	for currentNode.name != "ZZZ" {
		instruction := rune(instructions[instructionCounter%len(instructions)])
		if instruction == 'L' {
			currentNode = currentNode.left
		} else {
			currentNode = currentNode.right
		}
		instructionCounter++
	}
	fmt.Println("Part 1: ", instructionCounter)
}
