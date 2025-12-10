package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func printStringArray(stringArr []string) {
	for _, x := range stringArr {
		fmt.Println(x)
	}
}

type Pair struct {
	a, b int
}

func readInput(scanner *bufio.Scanner) []Pair {

	pairs := make([]Pair, 0)

	for scanner.Scan() {

		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		println(stripped)
		spl := strings.Split(stripped, ",")
		//println(spl)
		fmt.Println(spl)
		printStringArray(spl)

		a, _ := strconv.Atoi(spl[0])
		b, _ := strconv.Atoi(spl[1])
		pair := Pair{a: a, b: b}
		pairs = append(pairs, pair)

	}

	return pairs
}

func printGrid(redTiles, greenTiles []Pair) {
	tiles := append(append([]Pair{}, redTiles...), greenTiles...)
	minX, maxX, minY, maxY := 0, 0, 0, 0
	for _, t := range tiles {
		if t.a < minX {
			minX = t.a
		}
		if t.a > maxX {
			maxX = t.a
		}
		if t.b < minY {
			minY = t.b
		}
		if t.b > maxY {
			maxY = t.b
		}
	}

	width := maxX - minX + 1
	height := maxY - minY + 1

	grid := make([][]rune, height)
	for y := range grid {
		grid[y] = make([]rune, width)
		for x := range grid[y] {
			grid[y][x] = '.'
		}
	}

	draw := func(tiles []Pair, mark rune) {
		for _, t := range tiles {
			grid[t.b-minY][t.a-minX] = mark
		}
	}

	draw(greenTiles, 'G')
	draw(redTiles, 'R')

	for _, row := range grid {
		fmt.Println(string(row))
	}
}

func getPathBetweenCoords(from, to Pair) []Pair {
	path := make([]Pair, 0)

	startX, endX := from.a, to.a
	if startX > endX {
		startX, endX = endX, startX
	}
	startY, endY := from.b, to.b
	if startY > endY {
		startY, endY = endY, startY
	}

	for x := startX; x <= endX; x++ {
		for y := startY; y <= endY; y++ {
			path = append(path, Pair{a: x, b: y})
		}
	}

	return path
}

func getRectangleSize(start, end Pair) int {
	width := end.a - start.a + 1
	height := end.b - start.b + 1
	return width * height
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	pairs := readInput(scanner)
	println("Machines:")
	println(pairs)
	fmt.Println(pairs)
	fmt.Println("Num pairs:", len(pairs))

	outline := make([]Pair, 0)
	for i, x := range pairs {
		next := (i + 1) % len(pairs)
		y := pairs[next]
		if x.a == y.a {
			// vertical line
			path := getPathBetweenCoords(x, y)
			outline = append(outline, path...)
		} else if x.b == y.b {
			// horizontal line
			path := getPathBetweenCoords(x, y)
			outline = append(outline, path...)
		}
	}
	printGrid(pairs, outline)

	p1 := 0
	for i, x := range pairs {
		for j, y := range pairs {
			if i != j {
				area := getRectangleSize(x, y)
				p1 = max(p1, area)
			}
		}
	}

	fmt.Println("Part 1:", p1)

}
