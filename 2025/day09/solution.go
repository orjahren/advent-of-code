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

func readInput(scanner *bufio.Scanner) []Machine {

	machines := make([]Machine, 0)

	for scanner.Scan() {

		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		println(stripped)
		spl := strings.Split(stripped, " ")
		//println(spl)
		fmt.Println(spl)
		printStringArray(spl)

		for _, x := range spl {
			if x[0] == '(' {
			} else if x[0] == '{' {

			}
		}

		if len(stripped) == 0 {
		}

	}

	return machines
}

type Machine struct {
	target        []rune
	opertions     []Operation
	joltageTarget []int
}

type State struct {
	target, current []rune
	history         []Operation
	currentJoltages []int
	cnt             int
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

	p1 := 0
	for i, machine := range machines {
		// print progress status
		println("Status: ", i, "/", len(machines))

		fmt.Println("*** Processing machine", i, "->", machine)
		p1steps := -1 //solveMachineP1(machine)
		//fmt.Println("Machine", i, "solved in", p1steps, "steps")
		p1 += p1steps

	}

	fmt.Println("Part 1:", p1)

}
