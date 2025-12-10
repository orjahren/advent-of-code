package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
	"strconv"
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

func parseJoltage(joltage string) []int {
	len := len(joltage)
	println(len)
	joltages := make([]int, 0)
	fmt.Println(joltage)
	spl := strings.Split(joltage, ",")
	fmt.Println(spl)
	for _, x := range spl {
		parsed, err := strconv.Atoi(strings.Trim(x, "{}"))
		if err != nil {
			fmt.Println("Error parsing joltage:", err)
			continue
		}
		// TODO: Hva er en sane max?
		if parsed >= 0 && parsed < 127 {
			fmt.Println("Joltage: Parset ", x, " til ", parsed)
			joltages = append(joltages, parsed)
		}
	}
	fmt.Println(joltages)
	return joltages
}

func readInput(scanner *bufio.Scanner) []Machine {

	machines := make([]Machine, 0)

	for scanner.Scan() {
		operations := make([]Operation, 0)
		var joltage []int

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

				joltage = parseJoltage(x)
			}
		}

		if len(stripped) == 0 {
		}

		var m Machine = Machine{parseTarget(targetRepr), operations, joltage}
		machines = append(machines, m)
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

func newStateIsSane(state State, targetMachine Machine) bool {
	// Check that no joltage exceeds target joltage
	for i, jolt := range state.currentJoltages {
		if jolt > targetMachine.joltageTarget[i] {
			return false
		}
	}
	return true
}
func solveMachineP1(machine Machine) int {
	initialState := State{machine.target, make([]rune, len(machine.target)), make([]Operation, 0), make([]int, len(machine.joltageTarget)), 0}

	queue := make([]State, 0)
	queue = append(queue, initialState)

	for len(queue) > 0 {
		currentState := queue[0]
		queue = queue[1:]

		//println("Processing state:")
		//fmt.Println(currentState)

		// Check if we reached the target
		if string(currentState.current) == string(currentState.target) {
			return len(currentState.history)
		}

		// Generate new states by applying each operation
		for _, op := range machine.opertions {
			newState := State{
				target:          currentState.target,
				current:         make([]rune, len(currentState.current)),
				history:         append(currentState.history, op),
				currentJoltages: make([]int, len(currentState.currentJoltages)),
			}
			copy(newState.current, currentState.current)
			copy(newState.currentJoltages, currentState.currentJoltages)

			// Apply operation
			for _, idx := range op.indeces {
				if idx >= 0 && idx < len(newState.current) {
					newState.current[idx] ^= 1 // Toggle bit
					// increment joltages
				}
			}

			queue = append(queue, newState)

		}
	}

	return -1 // No solution found
}

func solveMachineBfsP2(machine Machine) int {
	initialState := State{machine.target, make([]rune, len(machine.target)), make([]Operation, 0), make([]int, len(machine.joltageTarget)), 0}
	println("Joltage target:")
	fmt.Println(machine.joltageTarget)

	//println("Initial joltage:")
	fmt.Println(initialState.currentJoltages)

	queue := make([]State, 0)
	queue = append(queue, initialState)

	// Apply operations until we find a solution that makes the current state
	// match the target state
	// Assume what we may need to apply the same steps several times

	for len(queue) > 0 {
		currentState := queue[0]
		queue = queue[1:]

		// println("Processing state:")
		// fmt.Println(currentState)

		if slices.Equal(currentState.currentJoltages, machine.joltageTarget) {
			return currentState.cnt
		}

		// Generate new states by applying each operation
		for _, op := range machine.opertions {
			newState := State{
				target:  currentState.target,
				current: make([]rune, len(currentState.current)),
				//history:         append(currentState.history, op),
				currentJoltages: make([]int, len(currentState.currentJoltages)),
				cnt:             currentState.cnt + 1,
			}
			copy(newState.current, currentState.current)
			copy(newState.currentJoltages, currentState.currentJoltages)

			// Apply operation
			for _, idx := range op.indeces {
				if idx >= 0 && idx < len(newState.current) {
					newState.current[idx] ^= 1 // Toggle bit
					// increment joltages
					newState.currentJoltages[idx] += 1
				}
			}

			if newStateIsSane(newState, machine) {
				//continue
				queue = append(queue, newState)
			}

		}
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
	p2 := 0
	for i, machine := range machines {
		// print progress status
		println("Status: ", i, "/", len(machines))

		fmt.Println("*** Processing machine", i, "->", machine)
		p1steps := -1 //solveMachineP1(machine)
		//fmt.Println("Machine", i, "solved in", p1steps, "steps")
		p1 += p1steps

		p2steps := solveMachineBfsP2(machine)
		fmt.Println("Machine", i, "solved in", p2steps, "steps")
		p2 += p2steps
	}

	fmt.Println("Part 1:", p1)
	fmt.Println("Part 2:", p2)

}
