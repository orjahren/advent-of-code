package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func readInput(scanner *bufio.Scanner) []int {
	numbers := make([]int, 0)
	for scanner.Scan() {
		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		if len(stripped) == 0 {
			return numbers
		}
		parsed, _ := strconv.Atoi(stripped)
		numbers = append(numbers, parsed)
	}
	return numbers
}

type Monkey struct {
	initialNumber                int
	secrets, deltas, priceAtTime []int
	sellWhen                     int
}

func whereMonkeyHasDeltaSequence(monkey Monkey, sequence []int) int {
	// TODO: Kan gjøre dette med builtins??
	for i, delta := range monkey.deltas {
		if delta == sequence[0] {
			found := true
			if i+len(sequence) > len(monkey.deltas) {
				break
			}
			for j, seqDelta := range sequence {
				if monkey.deltas[i+j] != seqDelta {
					found = false
					break
				}
			}
			if found {
				return i
			}
		}
	}
	return -1
}

func getValueOfDeltaSequence(monkeys []Monkey, sequence []int) int {
	sum := 0
	for _, m := range monkeys {
		startIdx := whereMonkeyHasDeltaSequence(m, sequence)
		if startIdx != -1 {
			sum += m.priceAtTime[startIdx+3]

		}

	}
	return sum
}

func getBestDeltaSequence(monkeys []Monkey, sequenceSize int) []int {
	currMax := -1
	var bestSequence []int
	for _, m := range monkeys {
		for i := 0; i < 2000; i++ {
			windowStart := i
			windowEnd := i + sequenceSize
			if windowEnd > 2000 {
				break
			}
			seq := m.deltas[windowStart:windowEnd]
			windowSum := getValueOfDeltaSequence(monkeys, seq)
			if windowSum > currMax {
				currMax = windowSum
				bestSequence = seq
			}
		}
	}
	return bestSequence
}

func getOptimalTimeToBuy(monkeys []Monkey) int {
	bestSequence := getBestDeltaSequence(monkeys, 4)
	fmt.Println("Best sequence:", bestSequence)

	res := 0
	for _, m := range monkeys {
		idx := whereMonkeyHasDeltaSequence(m, bestSequence)
		if idx != -1 {
			println("Monkey", m.secrets[0], " selger på index:", idx)
			res += m.priceAtTime[idx+3]
		}
	}

	return res
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	nums := readInput(scanner)

	// nums = []int{123}

	p1 := 0
	monkeys := make([]Monkey, 0)
	for _, x := range nums {
		print(x)
		print(": ")
		m := Monkey{x, make([]int, 0), make([]int, 0), make([]int, 0), -1}
		m.secrets = append(m.secrets, x)
		m.deltas = append(m.deltas, x%10)
		m.priceAtTime = append(m.priceAtTime, x%10)
		n := x
		k := 2000
		secretNumber := n
		for i := range k {
			// step 1
			tmp := secretNumber * 64
			secretNumber ^= tmp
			secretNumber %= 16777216

			// step 2
			tmp = secretNumber / 32
			secretNumber ^= tmp
			secretNumber %= 16777216

			// step 3
			tmp = secretNumber * 2048
			secretNumber ^= tmp
			secretNumber %= 16777216

			m.secrets = append(m.secrets, secretNumber)

			lastDigit := secretNumber % 10
			prevLastDigit := (m.secrets[i]) % 10
			delta := lastDigit - prevLastDigit
			m.deltas = append(m.deltas, delta)
			m.priceAtTime = append(m.priceAtTime, lastDigit)
		}
		monkeys = append(monkeys, m)
		println(m.secrets[2000])
		p1 += m.secrets[2000]
	}
	fmt.Println("Part 1:", p1)

	p2 := getOptimalTimeToBuy(monkeys)
	fmt.Println("Part 2:", p2)

}
