package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func printStringArray(stringArr []string) {
	for _, x := range stringArr {
		fmt.Println(x)
	}
}

func parseTarget(target string) []rune {
	println(target)
	len := len(target)
	println(len)
	runes := make([]rune, len-2)
	for i, x := range target {
		if x == '#' {
			runes[i-1] = 1

		}
		//else if x == '#' {
		//}
	}
	fmt.Println(runes)
	return runes
}

func parseOperation(op string) Operation {
	len := len(op)
	println(len)
	indeces := make([]int, 0)
	for _, x := range op {
		parsed := int(x - '0')
		// TODO: Hva er en sane max?
		if parsed >= 0 && parsed < 127 {
			fmt.Println("Parset ", x, " til ", parsed)

			indeces = append(indeces, parsed)

		}
	}
	fmt.Println(indeces)
	return Operation{indeces}
}

func readInput(scanner *bufio.Scanner) []Machine {

	machines := make([]Machine, 0)

	for scanner.Scan() {
		operations := make([]Operation, 0)
		joltages := make([]string, 0)

		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		println(stripped)
		spl := strings.Split(stripped, " ")
		//println(spl)
		fmt.Println(spl)
		printStringArray(spl)

		targetRepr := spl[0]
		for _, x := range spl {
			if x[0] == '(' {
				operations = append(operations, parseOperation((x)))
			} else if x[0] == '{' {

				joltages = append(joltages, x)
			}
		}

		if len(stripped) == 0 {
		}

		// TODO: Virker ikke som man trenger joltages for p1
		var m Machine = Machine{parseTarget(targetRepr), operations, nil}
		machines = append(machines, m)
	}

	return machines
}

type Machine struct {
	target    []rune
	opertions []Operation
	joltages  []rune
}

type State struct {
	target, current []rune
	history         []Operation
}
type Operation struct {
	indeces []int
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	machines := readInput(scanner)
	println("Machines:")
	println(machines)
	fmt.Println(machines)
	fmt.Println("Num machines:", len(machines))

	for i, machine := range machines {
		fmt.Println("*** Processing machine", i, "->", machine)
	}

	p1 := 0

	fmt.Println("Part 1:", p1)

}
