package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type Line struct {
	value   int
	numbers []int
}

func parseLine(line string) Line {
	spl := strings.Split(line, "")
	ret := make([]Line, len(spl))
	for colIdx := range spl {
		c := Line{colIdx, []int{}}
		ret[colIdx] = c
	}
	return Line{}
}

func readInput(scanner *bufio.Scanner) []Line {
	lines := make([]Line, 0)
	i := 0
	for scanner.Scan() {
		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		if len(stripped) == 0 {
			return lines
		}
		u := parseLine(stripped)
		lines = append(lines, u)
		i++
	}
	return lines
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	lines := readInput(scanner)
	fmt.Println(lines)

	p1 := -1

	fmt.Println("Part 1:", p1)

}
