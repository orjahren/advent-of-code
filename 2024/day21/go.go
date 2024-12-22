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
	ch := make(chan int)
	defer close(ch)
	for _, m := range monkeys {
		go func() {
			startIdx := whereMonkeyHasDeltaSequence(m, sequence)
			if startIdx != -1 {

				ch <- m.priceAtTime[startIdx+3]

			} else {
				ch <- 0
			}
		}()

	}
	sum := 0
	for range monkeys {
		sum += <-ch
	}
	return sum
}

type SeqResult struct {
	sequence []int
	value    int
}

func getBestDeltaSequence(monkeys []Monkey, sequenceSize int) []int {
	ch := make(chan SeqResult)
	defer close(ch)
	currMax := -1
	var bestSequence []int
	for _, m := range monkeys {
		for i := 0; i < 2000; i++ {
			go func() {
				windowStart := i
				windowEnd := i + sequenceSize
				if windowEnd > 2000 {
					ch <- SeqResult{nil, -1}
					return
				}
				seq := m.deltas[windowStart:windowEnd]
				windowSum := getValueOfDeltaSequence(monkeys, seq)
				ch <- SeqResult{seq, windowSum}
			}()
		}
	}
	deler := float64(len(monkeys))
	for counter := range monkeys {
		percentage := float64(counter) / deler
		for range 2000 {
			res := <-ch
			windowSum := res.value
			seq := res.sequence
			if windowSum > currMax {
				currMax = windowSum
				bestSequence = seq
			}
		}
		fmt.Printf("Progress: %.2f%%\n", percentage*100)
	}
	return bestSequence
}

func getOptimalTimeToBuy(monkeys []Monkey) int {
	bestSequence := getBestDeltaSequence(monkeys, 4)
	fmt.Println("Best sequence:", bestSequence)

	ch := make(chan int)
	defer close(ch)
	for _, m := range monkeys {
		go func() {
			idx := whereMonkeyHasDeltaSequence(m, bestSequence)
			if idx != -1 {
				println("Monkey", m.secrets[0], " selger på index:", idx)
				ch <- m.priceAtTime[idx+3]
			} else {
				ch <- 0
			}
		}()

	}
	res := 0
	for range monkeys {
		res += <-ch
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
