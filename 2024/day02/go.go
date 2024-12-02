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
	diff := math.Abs(float64(a - b))
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
	if report[0] < report[1] {
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
	spl := strings.Split(report, " ")
	reportInts := make([]int, len(spl))
	for i := range reportInts {
		reportInts[i], _ = strconv.Atoi(string(spl[i]))
	}
	if reportIsSafe(reportInts) {
		ch <- 1
	} else {
		ch <- 0
	}
}

func getIntSliceWithoutIdx(arr []int, idx int) []int {
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
	spl := strings.Split(report, " ")
	reportInts := make([]int, len(spl))
	for i := range reportInts {
		reportInts[i], _ = strconv.Atoi(string(spl[i]))
	}
	if reportIsSafe(reportInts) {
		ch <- 1
	} else {
		// Pro gamer move time
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
			reports = append(reports, line)
		}
	}
	p1 := part1(reports)
	fmt.Println("Part 1:", p1)
	p2 := part2(reports)
	fmt.Println("Part 2:", p2)
}
