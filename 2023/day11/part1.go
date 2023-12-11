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
	for line != "" {
		trimmedLine := strings.TrimSpace(line)
		fmt.Println(trimmedLine)
		line, _ = reader.ReadString('\n')
		for i, char := range trimmedLine {
			if char == '#' {
				p := Point{i, y}
				fmt.Println(p)
				points = append(points, p)
			}

		}
		y++
	}

}
