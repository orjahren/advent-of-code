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

func dealWithString(inp string, out chan int) {

	spl := strings.Split(inp, ",")
	spenn1 := strings.Split(spl[0], "-")
	spenn2 := strings.Split(spl[1], "-")

	a, _ := strconv.Atoi(spenn1[0])
	b, _ := strconv.Atoi(spenn1[1])

	x, _ := strconv.Atoi(spenn2[0])
	y, _ := strconv.Atoi(spenn2[1])
	// Spenn1 inneholder hele spenn2
	if a <= x && b >= y {
		out <- 1
	} else if x <= a && y >= b {
		// Spenn2 inneholder hele spenn1
		out <- 1
	} else {
		out <- 0
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

func part2(inp string, out chan int) {

	spl := strings.Split(inp, ",")
	spenn1 := strings.Split(spl[0], "-")
	spenn2 := strings.Split(spl[1], "-")

	a, _ := strconv.Atoi(spenn1[0])
	b, _ := strconv.Atoi(spenn1[1])

	x, _ := strconv.Atoi(spenn2[0])
	y, _ := strconv.Atoi(spenn2[1])
	if doesOverlap(a, b, x, y) || doesOverlap(x, y, a, b) {
		out <- 1
	} else {
		out <- 0
	}

}

func main() {
	f, err := os.Open("input")
	//f, err := os.Open("small")
	check(err)
	defer f.Close()
	scanner := bufio.NewScanner(f)
	isOverlapping := make(chan int)
	anyOverlap := make(chan int)

	numberOfBlocks := 0
	for scanner.Scan() {
		text := scanner.Text()
		go dealWithString(text, isOverlapping)
		go part2(text, anyOverlap)
		numberOfBlocks++
	}
	readBlocks := 0
	res := 0
	for true {
		res += <-isOverlapping
		readBlocks++
		if readBlocks == numberOfBlocks {
			break
		}
	}
	fmt.Println("Part 1: ", res)
	readBlocks = 0
	res = 0
	for true {
		res += <-anyOverlap
		readBlocks++
		if readBlocks == numberOfBlocks {
			break
		}
	}

	fmt.Println("Part 2: ", res)
}
