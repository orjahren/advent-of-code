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
	/*
		spl := strings.Split(line, "")
		a, _ := strconv.Atoi(spl[0])
		b, _ := strconv.Atoi(spl[1])
	*/
	return nil
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

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	coordinates := readInput(scanner)
	fmt.Println(coordinates)

	p1 := -1
	fmt.Println("Part 1:", p1)
}
