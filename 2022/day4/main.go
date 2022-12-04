package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}

func max(x, y int) int {
	if x > y {
		return x
	}
	return y
}

func doesOverlap(p, q, r, s int) bool {

	return max(p, r) <= min(q, s)
}

func doPart2(a, b, x, y int, part2 chan int) {

	if doesOverlap(a, b, x, y) || doesOverlap(x, y, a, b) {
		part2 <- 1
	} else {
		part2 <- 0
	}
}

func dealWithString(inp string, part1 chan int, part2 chan int) {

	spl := strings.Split(inp, ",")
	spenn1 := strings.Split(spl[0], "-")
	spenn2 := strings.Split(spl[1], "-")

	a, _ := strconv.Atoi(spenn1[0])
	b, _ := strconv.Atoi(spenn1[1])

	x, _ := strconv.Atoi(spenn2[0])
	y, _ := strconv.Atoi(spenn2[1])

	go doPart2(a, b, x, y, part2)

	// Spenn1 inneholder hele spenn2
	if a <= x && b >= y {
		part1 <- 1
	} else if x <= a && y >= b {
		// Spenn2 inneholder hele spenn1
		part1 <- 1
	} else {
		part1 <- 0
	}
}

func main() {
	f, err := os.Open("input")
	//f, err := os.Open("small")
	check(err)
	defer f.Close()
	scanner := bufio.NewScanner(f)
	completeOverlap := make(chan int)

	anyOverlap := make(chan int)

	numberOfBlocks := 0
	for scanner.Scan() {
		go dealWithString(scanner.Text(), completeOverlap, anyOverlap)
		numberOfBlocks++
	}
	readBlocks := 0
	part1Res := 0
	part2Res := 0
	for true {
		part1Res += <-completeOverlap
		part2Res += <-anyOverlap
		readBlocks++
		if readBlocks == numberOfBlocks {
			break
		}
	}
	fmt.Println("Part 1: ", part1Res)
	fmt.Println("Part 2: ", part2Res)
}
