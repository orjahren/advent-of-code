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

func findAndPropogateDistaceToPoint(from, to Point, part1ch, part2ch chan int, rowsOfOnlyDots, colsOfOnlyDots []int) {
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
	part2Fac := 1000000
	//part2Fac = 10
	//part2Fac = 100
	part1ch <- manhattanDistance + rowsBetween + colsBetween
	part2ch <- manhattanDistance + (rowsBetween * (part2Fac - 1)) + (colsBetween * (part2Fac - 1))

}

type Point struct {
	x, y, id int
}

func main() {
	//file, _ := os.Open("example")
	file, _ := os.Open("input")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')

	points := make([]Point, 0)
	rowCounter := 0
	rowsOfOnlyDots := make([]int, 0)
	colsOfOnlyDots := make([]int, 0)

	for line != "" {
		trimmedLine := strings.TrimSpace(line)
		fmt.Println(trimmedLine)
		line, _ = reader.ReadString('\n')
		rowHasOnlyDots := true
		for i, char := range trimmedLine {
			if char == '#' {
				p := Point{i, rowCounter, len(points) + 1}
				fmt.Println(p)
				points = append(points, p)
				rowHasOnlyDots = false
			}

		}
		if rowHasOnlyDots {
			rowsOfOnlyDots = append(rowsOfOnlyDots, rowCounter)
		}
		rowCounter++
	}

	for i := 0; i < rowCounter; i++ {
		colHasOnlyDots := true
		for _, point := range points {
			if point.x == i {
				colHasOnlyDots = false
			}
		}
		if colHasOnlyDots {
			colsOfOnlyDots = append(colsOfOnlyDots, i)
		}
	}
	// print what cols and rows have only dots
	fmt.Println(rowsOfOnlyDots)
	fmt.Println(colsOfOnlyDots)

	allPairsOfPoints := make([][]Point, 0)
	for _, from := range points {
		for _, to := range points {
			if from != to {
				// check for duplicates
				alreadyExists := false
				for _, pair := range allPairsOfPoints {
					if pair[0] == to && pair[1] == from || pair[0] == from && pair[1] == to {
						alreadyExists = true
					}
				}
				if alreadyExists {
					continue
				}

				allPairsOfPoints = append(allPairsOfPoints, []Point{from, to})
			}
		}
	}
	fmt.Println(allPairsOfPoints)

	part1ch := make(chan int)
	part2ch := make(chan int)
	//numsToExpect := (len(points) * len(points)) - len(points)
	for _, pair := range allPairsOfPoints {
		from := pair[0]
		to := pair[1]
		fmt.Println("From", from, "to", to)
		go findAndPropogateDistaceToPoint(from, to, part1ch, part2ch, rowsOfOnlyDots, colsOfOnlyDots)

	}
	var part1, part2 int
	for i := 0; i < len(allPairsOfPoints); i++ {
		//fmt.Println("Waiting for", i, "number")
		part1 += <-part1ch
		part2 += <-part2ch
	}
	fmt.Println("Number of pairs", len(allPairsOfPoints))
	fmt.Println("Part 1:", part1)
	fmt.Println("Part 2:", part2)

}

// First res: 904634704098. Too high.
// 2nd res: 98262072. Too low.
// 3rd: 904633799472. Corrcet.
