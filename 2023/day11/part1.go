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
		if row > from.y && row < to.y {
			rowsBetween++
		}
	}
	for _, col := range colsOfOnlyDots {
		if col > from.x && col < to.x {
			colsBetween++
		}
	}
	//fmt.Println("Rows between", rowsBetween)
	//fmt.Println("Cols between", colsBetween)
	return manhattanDistance + (rowsBetween * 2) + (colsBetween * 2)

}

func getDistanceToClosestPoint(a Point, points []Point, ch chan int, rowsOfOnlyDots, colsOfOnlyDots []int) {
	minDistance := int(math.Inf(1))
	var closestPoint Point
	for _, b := range points {
		if a != b {
			distance := getDistanceWithRecgardToSomeRowsAndColumnsCountingDouble(a, b, rowsOfOnlyDots, colsOfOnlyDots)
			if distance < minDistance {
				minDistance = distance
				closestPoint = b
			}
		}
	}
	fmt.Println("Closest point to", a, "is", closestPoint, "with distance", minDistance)
	ch <- minDistance
	//return minDistance
}

type Point struct {
	x, y, id int
}

func main() {
	file, _ := os.Open("example")
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

	ch := make(chan int)
	numsToExpect := 0
	for _, from := range points {
		//fmt.Println("From", from, "to", to)
		go getDistanceToClosestPoint(from, points, ch, rowsOfOnlyDots, colsOfOnlyDots)
		numsToExpect++

	}
	fmt.Println("Expecting", numsToExpect, "numbers")
	part1 := 0
	for i := 0; i < numsToExpect; i++ {
		fmt.Println("Waiting for", i, "number")
		part1 += <-ch
	}
	fmt.Println("Part 1:", part1)

}
