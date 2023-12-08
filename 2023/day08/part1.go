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

func readFileAndStructureInput(reader bufio.Reader) ([]Node, map[string]*Node) {
	nodes := make([]Node, 0)
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
		// TODO: fører dette til noe wack med at noden får ny minneadresse?
		nodes[i] = node
	}
	fmt.Println("\t Har satt opp pekere")
	return nodes, nameToNodeMap
}

func main() {
	//file, _ := os.Open("input")
	file, _ := os.Open("example")
	reader := bufio.NewReader(file)

	instructions, _ := reader.ReadString('\n')
	fmt.Println(instructions)
	reader.ReadString('\n')

	nodes, nameToNodeMap := readFileAndStructureInput(*reader)

	fmt.Println(nodes)
	fmt.Println(nameToNodeMap)
}
