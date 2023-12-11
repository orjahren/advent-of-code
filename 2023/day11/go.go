package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strings"
)

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func getTaxiCabDistance(x1, y1, x2, y2 int) int {
	return abs(x1-x2) + abs(y1-y2)
}

func findAndPropogateDistaceToPoint(pair Pair, part1ch, part2ch chan int, rowsOfOnlyDots, colsOfOnlyDots []int) {
	from := pair.A
	to := pair.B
	manhattanDistance := getTaxiCabDistance(from.x, from.y, to.x, to.y)
	rowsBetween := 0
	colsBetween := 0
	for _, row := range rowsOfOnlyDots {
		if math.Max(float64(to.y), float64(from.y)) > float64(row) && math.Min(float64(from.y), float64(to.y)) < float64(row) {
			rowsBetween++
		}
	}
	for _, col := range colsOfOnlyDots {
		if math.Max(float64(to.x), float64(from.x)) > float64(col) && math.Min(float64(from.x), float64(to.x)) < float64(col) {
			colsBetween++
		}
	}
	part1ch <- manhattanDistance + rowsBetween + colsBetween
	part2ch <- manhattanDistance + (rowsBetween * 99999) + (colsBetween * 99999)

}

type Point struct {
	x, y, id int
}
type Pair struct {
	A, B Point
}

func main() {
	file, _ := os.Open("input")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')

	points := make([]Point, 0)
	rowCounter := 0
	rowsOfOnlyDots := make([]int, 0)

	colHasPointsFlags := make([]int, len(line))

	for line != "" {
		trimmedLine := strings.TrimSpace(line)
		line, _ = reader.ReadString('\n')
		rowHasOnlyDots := true
		for i, char := range trimmedLine {
			if char == '#' {
				p := Point{i, rowCounter, len(points) + 1}
				points = append(points, p)
				rowHasOnlyDots = false
				colHasPointsFlags[i] = 1
			}

		}
		if rowHasOnlyDots {
			rowsOfOnlyDots = append(rowsOfOnlyDots, rowCounter)
		}
		rowCounter++
	}
	colsOfOnlyDots := make([]int, 0)
	for i, flag := range colHasPointsFlags {
		if flag == 0 {
			colsOfOnlyDots = append(colsOfOnlyDots, i)
		}
	}

	allPairsOfPoints := make(map[Pair]bool)
	part1ch := make(chan int)
	part2ch := make(chan int)
	for _, from := range points {
		for _, to := range points {
			if from != to {
				pair := Pair{A: from, B: to}
				reversePair := Pair{A: to, B: from}
				if _, exists := allPairsOfPoints[pair]; exists || allPairsOfPoints[reversePair] {
					continue
				}
				go findAndPropogateDistaceToPoint(pair, part1ch, part2ch, rowsOfOnlyDots, colsOfOnlyDots)
				allPairsOfPoints[pair] = true
			}
		}
	}

	var part1, part2 int
	for i := 0; i < len(allPairsOfPoints); i++ {
		part1 += <-part1ch
		part2 += <-part2ch
	}
	fmt.Println("Part 1:", part1, "\nPart 2:", part2)
}
