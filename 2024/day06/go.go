package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type Coordinate struct {
	row, column int
	value       rune
}

func lineToCor(line string, rowCount int) []Coordinate {
	spl := strings.Split(line, "")
	ret := make([]Coordinate, len(spl))
	for colIdx, x := range spl {
		fmt.Println(colIdx, x)

		c := Coordinate{rowCount, colIdx, rune(x[0])}
		ret[colIdx] = c
	}
	return ret
}

func readInput(scanner *bufio.Scanner) [][]Coordinate {
	coordinates := make([][]Coordinate, 0)
	i := 0
	for scanner.Scan() {
		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		if len(stripped) == 0 {
			return coordinates
		}
		u := lineToCor(stripped, i)
		coordinates = append(coordinates, u)
		i++
	}
	return coordinates
}

func getStartPosition(coordinates [][]Coordinate) Coordinate {
	for _, row := range coordinates {
		for _, cor := range row {
			if cor.value == '^' {
				return cor
			}
		}
	}
	panic("No start position found")
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	coordinates := readInput(scanner)
	fmt.Println(coordinates)
	fmt.Println("Rows:", len(coordinates))
	fmt.Println("Columns:", len(coordinates[0]))

	startPos := getStartPosition(coordinates)
	fmt.Println("Start position:", startPos)

	p1 := -1
	fmt.Println("Part 1:", p1)
}
