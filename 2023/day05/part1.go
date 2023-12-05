package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func stringContainsMap(s string) bool {
	return strings.Contains(s, "map")
}

func main() {
	println("Hello, World!")
	file, _ := os.Open("example")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')
	stripped := strings.TrimSpace(line)
	fmt.Println(stripped)

	allLines := make([]string, 0)
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		stripped := strings.TrimSpace(line)
		fmt.Println(stripped)
		allLines = append(allLines, stripped)
	}
	fmt.Println(allLines)
	fmt.Println(len(allLines))
}
