package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Equation struct {
	value   int64
	numbers []int64
}

func parseLine(line string) Equation {
	spl := strings.Split(line, " ")
	fmt.Println(spl)
	nums := make([]int64, len(spl)-1)
	for numIdx := 1; numIdx < len(spl); numIdx++ {
		x, _ := strconv.Atoi(spl[numIdx])
		nums[numIdx-1] = int64(x)
	}
	spl[0] = strings.Replace(spl[0], ":", "", -1)
	val, _ := strconv.Atoi(spl[0])
	return Equation{int64(val), nums}
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

func solveEquationP1(equation Equation, curr, numIdx int) int {
	operators := []string{"+", "*"}
	if int(numIdx) == len(equation.numbers) {
		if curr == int(equation.value) {
			return curr
		}
		return 0
	}
	for _, op := range operators {
		if op == "+" {
			x := solveEquationP1(equation, curr+int(equation.numbers[numIdx]), numIdx+1)
			if x != -1 {
				return int(equation.value)
			}
		} else {
			x := solveEquationP1(equation, curr*int(equation.numbers[numIdx]), numIdx+1)
			if x != -1 {
				return int(equation.value)
			}
		}
	}
	return 0
}

func raise(base, exp int) int {
	result := 1
	for i := 0; i < exp; i++ {
		result *= base
	}
	return result
}

func getBaseRep(num, base int) string {
	if num == 0 {
		return "0"
	}
	res := ""
	for num > 0 {
		res = strconv.FormatInt(int64(num%base), 10) + res
		num /= base
	}
	return res
}

const testTarget = 7290

func solveEquationP2(equation Equation) int {
	if equation.value == testTarget {
		fmt.Println("[top] Origial equation: ", equation)
	}
	slots := len(equation.numbers) - 1
	for p := 0; p < raise(3, slots); p++ {
		res := equation.numbers[0]
		s := getBaseRep(p, 3)
		l := len(s)

		for b := 0; b < slots; b++ {
			bv := 0
			if l-b-1 >= 0 {
				bv = int(s[l-b-1] - '0')
			}
			if bv == 0 {
				res += equation.numbers[b+1]
			} else if bv == 1 {
				res *= equation.numbers[b+1]
			} else if bv == 2 {
				res, _ = strconv.ParseInt(fmt.Sprintf("%d%d", res, equation.numbers[b+1]), 10, 64)
			}
		}

		if res == equation.value {
			return int(equation.value)
		}
	}

	return 0
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	equations := readInput(scanner)
	fmt.Println(equations)

	p1 := 0
	for _, eq := range equations {
		p1 += solveEquationP1(eq, 0, 0)
	}

	fmt.Println("Part 1:", p1)

	p2 := 0
	for _, eq := range equations {
		x := solveEquationP2(eq)
		if x != 0 {
			p2 += int(x)
		}
	}
	fmt.Println("Part 2:", p2)

}
