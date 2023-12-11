package main

import (
	"bufio"
	"fmt"
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

type Point struct {
	x, y int
}

func main() {
	file, _ := os.Open("example")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')

	points := make([]Point, 0)
	y := 0
	rowsOfOnlyDots := make([]int, 0)
	colsOfOnlyDots := make([]int, 0)

	for line != "" {
		trimmedLine := strings.TrimSpace(line)
		fmt.Println(trimmedLine)
		line, _ = reader.ReadString('\n')
		rowHasOnlyDots := true
		for i, char := range trimmedLine {
			if char == '#' {
				p := Point{i, y}
				fmt.Println(p)
				points = append(points, p)
				rowHasOnlyDots = false
			}

		}
		if rowHasOnlyDots {
			rowsOfOnlyDots = append(rowsOfOnlyDots, y)
		}
		y++
	}

	for i := 0; i < y; i++ {
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

}
