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

func getSecretNumber(n, k int) int {
	secretNumber := n
	for range k {
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

	}
	return secretNumber
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	nums := readInput(scanner)

	p1 := 0
	for _, x := range nums {
		print(x)
		print(": ")
		sn := getSecretNumber(x, 2000)
		p1 += sn
		println(sn)
	}
	fmt.Println("Part 1:", p1)

}
