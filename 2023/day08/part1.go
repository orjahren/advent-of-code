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
	name           string
	left           *Node
	right          *Node
	nameOfLeft     string
	nameOfRight    string
	selfVisitCount int
}

func readFileAndStructureInput(reader bufio.Reader) ([]*Node, map[string]*Node) {
	nodes := make([]*Node, 0)
	nameToNodeMap := make(map[string]*Node)

	onlyLettersRegex := regexp.MustCompile("[a-zA-Z]+")
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		fmt.Println("Spl: ")
		spl := strings.Split(line, " ")
		fmt.Println(len(spl))
		if len(spl) > 1 {
			var node Node
			fmt.Println(spl)
			for i, s := range spl {
				fmt.Println(i, ": "+s)
			}
			letters := onlyLettersRegex.FindAllString(line, -1)
			fmt.Println("Letters: ", letters)
			node.name = letters[0]
			node.nameOfLeft = letters[1]
			node.nameOfRight = letters[2]
			fmt.Println(node)
			nodes = append(nodes, &node)
			nameToNodeMap[node.name] = &node
		}
	}
	fmt.Println(nodes)
	fmt.Println(nameToNodeMap)
	fmt.Println("\t Har laget alle noder")
	fmt.Println("\t Setter opp pekere")
	for i := range nodes {
		node := nodes[i]
		node.left = nameToNodeMap[node.nameOfLeft]
		node.right = nameToNodeMap[node.nameOfRight]
	}
	fmt.Println("\t Har satt opp pekere")
	return nodes, nameToNodeMap
}

func main() {
	//file, _ := os.Open("input")
	file, _ := os.Open("example")
	//file, _ := os.Open("ex2")
	reader := bufio.NewReader(file)

	instructions, _ := reader.ReadString('\n')
	instructions = strings.TrimSuffix(instructions, "\n")
	fmt.Println(instructions)
	reader.ReadString('\n')

	nodes, nameToNodeMap := readFileAndStructureInput(*reader)

	fmt.Println(nodes)
	fmt.Println(nameToNodeMap)

	//startNode := nameToNodeMap["AAA"]
	startNode := nodes[0]
	fmt.Println("StartNode:", startNode)
	res := 0
	i := 0
	currentNode := startNode
	//os.Exit(0)
	selfVisitLimit := 10
	for (*currentNode).name != "ZZZ" {
		fmt.Println("Current node: ", currentNode)
		res++
		(*currentNode).selfVisitCount++
		if (*currentNode).selfVisitCount > selfVisitLimit {
			fmt.Println("Self visit count exceeded")
			os.Exit(0)
		}
		instruction := getInstruction(i, instructions)
		fmt.Println("Instruction: ", rune(instruction))
		if instruction == 'L' {
			currentNode = currentNode.left
		} else {
			currentNode = currentNode.right
		}
		i++
	}
	fmt.Println("har kommet til ", currentNode)
	fmt.Println("Res: ", res)
}
