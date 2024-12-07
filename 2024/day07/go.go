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

func solveEquation(equation Equation, curr, numIdx int) int {
	operators := []string{"+", "*"}
	if numIdx == len(equation.numbers) {
		if curr == equation.value {
			return 1
		}
		return -1
	}
	for _, op := range operators {
		if op == "+" {
			x := solveEquation(equation, curr+equation.numbers[numIdx], numIdx+1)
			if x != -1 {
				return equation.value
			}
		} else {
			x := solveEquation(equation, curr*equation.numbers[numIdx], numIdx+1)
			if x != -1 {
				return equation.value
			}
		}
	}
	return -1
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	equations := readInput(scanner)
	fmt.Println(equations)

	p1 := 0
	for _, eq := range equations {
		fmt.Println(eq)
		x := solveEquation(eq, 0, 0)
		if x != -1 {
			p1 += x

		}
	}

	fmt.Println("Part 1:", p1)

}
