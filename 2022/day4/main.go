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
	fmt.Println(spenn1, spenn2)

	a, _ := strconv.Atoi(spenn1[0])
	b, _ := strconv.Atoi(spenn1[1])

	x, _ := strconv.Atoi(spenn2[0])
	y, _ := strconv.Atoi(spenn2[1])
	// Spenn1 inneholder hele spenn2
	if a <= x && b >= y {
		fmt.Println("spenn1 inneholder 2: ", spenn1, spenn2)
		out <- 1
	} else if x <= a && y >= b {
		// Spenn2 inneholder hele spenn1
		fmt.Println("spenn2 inneholder 1: ", spenn2, spenn1)
		out <- 1
	} else {
		fmt.Println("ikke match: ", spenn1, spenn2)
		out <- 0
	}

}

func main() {
	//f, err := os.Open("input")
	f, err := os.Open("small")
	check(err)
	defer f.Close()
	scanner := bufio.NewScanner(f)
	isOverlapping := make(chan int)

	numberOfBlocks := 0
	for scanner.Scan() {
		text := scanner.Text()
		//fmt.Println("Leste dette: ", text)
		go dealWithString(text, isOverlapping)
		numberOfBlocks++
	}
	readBlocks := 0
	res := 0
	for true {
		res += <-isOverlapping
		readBlocks++
		if readBlocks == numberOfBlocks*1 {
			break
		}
	}
	fmt.Println("Part 1: ", res)
}
