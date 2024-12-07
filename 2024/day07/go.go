package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Equation struct {
	value   int
	numbers []int
}

func parseLine(line string) Equation {
	spl := strings.Split(line, " ")
	fmt.Println(spl)
	nums := make([]int, len(spl)-1)
	for numIdx := 1; numIdx < len(spl); numIdx++ {
		nums[numIdx-1], _ = strconv.Atoi(spl[numIdx])
	}
	spl[0] = strings.Replace(spl[0], ":", "", -1)
	val, _ := strconv.Atoi(spl[0])
	return Equation{val, nums}
}

func readInput(scanner *bufio.Scanner) []Equation {
	lines := make([]Equation, 0)
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
	equations := readInput(scanner)
	fmt.Println(equations)

	p1 := -1

	fmt.Println("Part 1:", p1)

}
