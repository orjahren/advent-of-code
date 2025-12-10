package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func printStringArray(stringArr []string) {
	for _, x := range stringArr {
		fmt.Println(x)
	}
}

type Pair struct {
	a, b int
}

func readInput(scanner *bufio.Scanner) []Pair {

	pairs := make([]Pair, 0)

	for scanner.Scan() {

		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		println(stripped)
		spl := strings.Split(stripped, ",")
		//println(spl)
		fmt.Println(spl)
		printStringArray(spl)

		a, _ := strconv.Atoi(spl[0])
		b, _ := strconv.Atoi(spl[1])
		pair := Pair{a: a, b: b}
		pairs = append(pairs, pair)

	}

	return pairs
}

func getRectangleSize(start, end Pair) int {
	width := end.a - start.a + 1
	height := end.b - start.b + 1
	return width * height
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	pairs := readInput(scanner)
	println("Machines:")
	println(pairs)
	fmt.Println(pairs)
	fmt.Println("Num pairs:", len(pairs))

	m := 0
	for i, x := range pairs {
		for j, y := range pairs {
			if i != j {
				area := getRectangleSize(x, y)
				m = max(m, area)
			}
		}
	}
	p1 := m

	fmt.Println("Part 1:", p1)

}
