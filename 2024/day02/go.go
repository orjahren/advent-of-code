package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

func diffOk(a, b int) bool {
	println("check diffs are OK:", a, b)
	diff := math.Abs(float64(a - b))
	println("Diff:", diff)
	return diff >= 1 && diff <= 3
}

func diffsAreOk(report []int) bool {
	diffStatus := true
	for i := range report {
		if (i + 1) >= len(report) {
			break
		}
		a := report[i]
		b := report[i+1]
		diffStatus = diffStatus && diffOk(a, b)
	}
	return diffStatus
}

func allSameDirection(report []int) bool {
	println("All same dir:")
	println(report[0], report[1])
	if report[0] < report[1] {
		println("Må vokse")
		for i := range report {
			if (i + 1) >= len(report) {
				break
			}
			if report[i] >= report[i+1] {
				return false
			}

		}
		return true

	} else {
		println("Må synke")
		for i := range report {
			if (i + 1) >= len(report) {
				break
			}
			if report[i] <= report[i+1] {
				return false
			}

		}
		return report[0] != report[1]
	}
}

func getScore(report string, ch chan int) {
	println("Getting score for ", report)
	spl := strings.Split(report, " ")
	reportInts := make([]int, len(spl))
	for i := range reportInts {
		reportInts[i], _ = strconv.Atoi(string(spl[i]))
	}
	fmt.Println(reportInts)
	// TODO: Kan kjøre disse paralellt
	if diffsAreOk(reportInts) && allSameDirection(reportInts) {
		println("\t\t", report, " ER SAFE")
		ch <- 1
	} else {
		println("\t\t", report, " ER UNSAFE")
		ch <- 0
	}
}

func part1(reports []string) int {
	ch := make(chan int)

	for _, report := range reports {
		println(report)
		go getScore(report, ch)
	}
	res := 0
	for range reports {
		res += <-ch
	}

	return res
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	reports := make([]string, 0)
	for scanner.Scan() {
		line := scanner.Text()
		line = strings.Trim(line, "\n")
		if len(line) > 0 {
			print("Line: ")
			fmt.Println(line)
			reports = append(reports, line)
		}

	}

	p1 := part1(reports)
	fmt.Println("Part 1:", p1)
}
