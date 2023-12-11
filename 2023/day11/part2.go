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

func getDistanceWithRecgardToSomeRowsAndColumnsCountingDouble(from, to Point, rowsOfOnlyDots, colsOfOnlyDots []int) int {
	manhattanDistance := getTaxiCabDistance(from.x, from.y, to.x, to.y)

	// how many rows and cols are between from and to on the only dot cols and rows
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
	//fmt.Println("Rows between", rowsBetween)
	//fmt.Println("Cols between", colsBetween)
	return manhattanDistance + (rowsBetween * 1) + (colsBetween * 1)

}

func findAndPropogateDistaceToPoint(from, to Point, ch chan int, rowsOfOnlyDots, colsOfOnlyDots []int) {
	distance := getDistanceWithRecgardToSomeRowsAndColumnsCountingDouble(from, to, rowsOfOnlyDots, colsOfOnlyDots)
	fmt.Println("From", from, "to", to, "distance", distance)
	ch <- distance
	//return minDistance
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

	ch := make(chan int)
	//numsToExpect := (len(points) * len(points)) - len(points)
	for _, pair := range allPairsOfPoints {
		//fmt.Println("From", from, "to", to)
		from := pair[0]
		to := pair[1]
		go findAndPropogateDistaceToPoint(from, to, ch, rowsOfOnlyDots, colsOfOnlyDots)

	}
	part1 := 0
	for i := 0; i < len(allPairsOfPoints); i++ {
		//fmt.Println("Waiting for", i, "number")
		part1 += <-ch
	}
	fmt.Println("Number of pairs", len(allPairsOfPoints))
	fmt.Println("Part 1:", part1)

}
