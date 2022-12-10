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

func drawCRT(reg int, pHorIdx *int) {
	if reg-1 <= *pHorIdx && reg+1 >= *pHorIdx {
		fmt.Print("█")
	} else {
		fmt.Print(" ")
	}
	*pHorIdx++
	if *pHorIdx >= 40 {
		*pHorIdx = 0
		fmt.Println("")
	}
}

func main() {
	f, _ := os.Open("input")
	defer f.Close()
	scanner := bufio.NewScanner(f)
	currentCycle := 0
	reg := 1
	part1Res := 0
	horIdx := 0
	var line string
	var pop1 int
	var pop2 int
	var pHorIdx *int = &horIdx

	fmt.Println("Part 2:")
	for true {
		currentCycle += 1
		part1Res += doPart1(currentCycle, reg)
		drawCRT(reg, pHorIdx)
		pop1 = pop2
		pop2 = 0
		if pop1 != 0 {
			reg += pop1
		} else {
			if scanner.Scan() {
				line = scanner.Text()
			}
		}
		if line[0] == 'a' {
			pop2, _ = strconv.Atoi(strings.Split(line, " ")[1])
		} else if !((line[0] == 'n') || pop1 != 0 || pop2 != 0) {
			break
		}
		line = " "
	}
	fmt.Println("Part 1:", part1Res)
}
