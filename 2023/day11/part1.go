package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	file, _ := os.Open("example")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')
	for line != "" {
		trimmedLine := strings.TrimSpace(line)
		fmt.Println(trimmedLine)
		line, _ = reader.ReadString('\n')
	}

}
