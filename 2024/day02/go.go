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

func reportIsSafe(report []int) bool {
	// TODO: Kan kjøre disse paralellt
	return diffsAreOk(report) && allSameDirection(report)
}

func getScoreP1(report string, ch chan int) {
	println("Getting score for ", report)
	spl := strings.Split(report, " ")
	reportInts := make([]int, len(spl))
	for i := range reportInts {
		reportInts[i], _ = strconv.Atoi(string(spl[i]))
	}
	fmt.Println(reportInts)
	if reportIsSafe(reportInts) {
		println("\t\t", report, " ER SAFE")
		ch <- 1
	} else {
		println("\t\t", report, " ER UNSAFE")
		ch <- 0
	}
}

func getIntSliceWithoutIdx(arr []int, idx int) []int {
	fmt.Println("SKAL SLICE ", idx, "FRA ", arr)
	ret := make([]int, len(arr)-1)
	pos := 0
	for i := range arr {
		if i != idx {
			ret[pos] = arr[i]
			pos++
		}

	}
	return ret
}

func getScoreP2(report string, ch chan int) {
	println("Getting score for ", report)
	spl := strings.Split(report, " ")
	reportInts := make([]int, len(spl))
	for i := range reportInts {
		reportInts[i], _ = strconv.Atoi(string(spl[i]))
	}
	fmt.Println(reportInts)
	if reportIsSafe(reportInts) {
		println("\t\t", report, " ER SAFE")
		ch <- 1
	} else {
		println("\t\t", report, " ER UNSAFE i original state")
		// Pro gamer move time
		println("Brute forcer...")
		for i := range reportInts {
			cand := getIntSliceWithoutIdx(reportInts, i)
			if reportIsSafe(cand) {
				ch <- 1
				return
			}
		}

		ch <- 0
	}
}
func part2(reports []string) int {
	ch := make(chan int)

	for _, report := range reports {
		println(report)
		go getScoreP2(report, ch)
	}
	res := 0
	for range reports {
		res += <-ch
	}

	return res
}

func part1(reports []string) int {
	ch := make(chan int)

	for _, report := range reports {
		println(report)
		go getScoreP1(report, ch)
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
	p2 := part2(reports)
	fmt.Println("Part 2:", p2)
}
