package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func doPart1(currentCycle, reg int) int {
	if currentCycle == 20 || currentCycle == 60 || currentCycle == 100 || currentCycle == 140 || currentCycle == 180 || currentCycle == 220 {
		return currentCycle * reg
	} else {
		return 0
	}
}
func check(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {
	fmt.Println("Hello world")
	f, err := os.Open("input")
	check(err)
	defer f.Close()

	scanner := bufio.NewScanner(f)

	//numberOfBlocks := 0
	currentCycle := 0
	reg := 1
	part1Res := 0

	var line string = " "
	var pop1 int = 0
	var pop2 int = 0

	for true {
		currentCycle += 1
		part1Res += doPart1(currentCycle, reg)
		//drawCRT()

		pop1 = pop2
		pop2 = 0

		if pop1 != 0 {
			reg += pop1
		} else {
			if scanner.Scan() {

				line = scanner.Text()
				fmt.Println("Leste: " + line)
			} else {

				line = " "
			}

		}

		if line[0] == 'a' {
			pop2, _ = strconv.Atoi(strings.Split(line, " ")[1])
			fmt.Println("Fikk parset: ", pop2)
		} else if !((line[0] == 'n') || pop1 != 0 || pop2 != 0) {
			break
		}
		line = " "
	}
	fmt.Println("Part 1:", part1Res)

}
