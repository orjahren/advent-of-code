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
	res := n
	for range k {
		res = res * 252533 % 33554393
	}
	return res
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	nums := readInput(scanner)

	p1 := 0
	for _, x := range nums {
		println(x)
		sn := getSecretNumber(x, 2000)
		p1 += sn
	}
	fmt.Println("Part 1:", p1)

}
