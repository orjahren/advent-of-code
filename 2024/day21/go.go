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

// TODO: Kan caches
func whereMonkeyHasDeltaSequence(monkey Monkey, sequence []int) int {
	for i := 0; i < len(monkey.deltas); i++ {
		delta := monkey.deltas[i]
		if delta == sequence[0] {
			if i+len(sequence) > len(monkey.deltas) {
				break
			}
			found := true
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
	value := 0
	for _, m := range monkeys {
		startIdx := whereMonkeyHasDeltaSequence(m, sequence)
		if startIdx != -1 {
			value += m.priceAtTime[startIdx+3]
		}
	}
	return value
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
	// indre løkke kjører 4 millioner ganger
	deler := float64(len(monkeys))
	for counter, m := range monkeys {
		percentage := float64(counter) / deler
		fmt.Printf("Initializing goroutines: %.2f%%\n", percentage*100)
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
	// indre løkke kjører 4 millioner ganger
	for counter := range monkeys {
		percentage := float64(counter) / deler
		fmt.Printf("Reading values: %.2f%%\n", percentage*100)
		for range 2000 {
			res := <-ch
			windowSum := res.value
			seq := res.sequence
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
	res := 0
	for _, m := range monkeys {
		idx := whereMonkeyHasDeltaSequence(m, bestSequence)
		if idx != -1 {
			res += m.priceAtTime[idx+3]
		}
	}
	return res
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	nums := readInput(scanner)

	p1 := 0
	monkeys := make([]Monkey, 0)
	for _, x := range nums {
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
		p1 += m.secrets[2000]
	}
	fmt.Println("Part 1:", p1)

	p2 := getOptimalTimeToBuy(monkeys)
	fmt.Println("Part 2:", p2)

}
