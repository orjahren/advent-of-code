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

func solveMachineBfs(machine Machine) int {
	initialState := State{machine.target, make([]rune, len(machine.target)), make([]Operation, 0)}
	println("Initial state:")
	fmt.Println(initialState)

	queue := make([]State, 0)
	queue = append(queue, initialState)

	// Apply operations until we find a solution that makes the current state
	// match the target state
	// Assume what we may need to apply the same steps several times
	steps := 0

	for len(queue) > 0 {
		currentState := queue[0]
		queue = queue[1:]

		// Check if we reached the target
		if string(currentState.current) == string(currentState.target) {
			return len(currentState.history)
		}

		// Generate new states by applying each operation
		for _, op := range machine.opertions {
			newState := State{
				target:  currentState.target,
				current: make([]rune, len(currentState.current)),
				history: append(currentState.history, op),
			}
			copy(newState.current, currentState.current)

			// Apply operation
			for _, idx := range op.indeces {
				if idx >= 0 && idx < len(newState.current) {
					newState.current[idx] ^= 1 // Toggle bit
				}
			}

			queue = append(queue, newState)

		}
		steps++
	}

	return -1 // No solution found
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
		fmt.Println("*** Processing machine", i, "->", machine)
		steps := solveMachineBfs(machine)
		fmt.Println("Machine", i, "solved in", steps, "steps")
		p1 += steps
	}

	fmt.Println("Part 1:", p1)

}
