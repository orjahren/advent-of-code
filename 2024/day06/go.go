package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type Coordinate struct {
	row, column int
	value       rune
	visitCount  int
}
type Direction int

const (
	UP Direction = iota
	RIGHT
	DOWN
	LEFT
)

var directions = []Direction{UP, RIGHT, DOWN, LEFT}

func getNextDirection(currentDirection Direction) Direction {
	for i, dir := range directions {
		if dir == currentDirection {
			fmt.Println("Next direction:", directions[(i+1)%len(directions)])
			println("Was:", currentDirection)
			return directions[(i+1)%len(directions)]
		}
	}
	panic("Unknown direction")
}

func lineToCor(line string, rowCount int) []Coordinate {
	spl := strings.Split(line, "")
	ret := make([]Coordinate, len(spl))
	for colIdx, x := range spl {
		fmt.Println(colIdx, x)

		c := Coordinate{rowCount, colIdx, rune(x[0]), 0}
		ret[colIdx] = c
	}
	return ret
}

func readInput(scanner *bufio.Scanner) [][]Coordinate {
	coordinates := make([][]Coordinate, 0)
	i := 0
	for scanner.Scan() {
		text := scanner.Text()
		stripped := strings.Trim(text, "\n")
		if len(stripped) == 0 {
			return coordinates
		}
		u := lineToCor(stripped, i)
		coordinates = append(coordinates, u)
		i++
	}
	return coordinates
}

func getStartPosition(coordinates [][]Coordinate) Coordinate {
	for _, row := range coordinates {
		for _, cor := range row {
			if cor.value == '^' {
				return cor
			}
		}
	}
	panic("No start position found")
}

func printGrid(coordinates [][]Coordinate) {
	for _, row := range coordinates {
		for _, cor := range row {
			fmt.Print(string(cor.value))
		}
		fmt.Println()
	}
}

func printGridWithPath(coordinates [][]Coordinate, path []Coordinate) {
	for _, row := range coordinates {
		for _, cor := range row {
			for _, p := range path {
				if cor.row == p.row && cor.column == p.column {
					fmt.Print("O")
					goto next
				}
			}
			fmt.Print(string(cor.value))
		next:
		}
		fmt.Println()
	}
}

func coordinateIsWithinBounds(cor Coordinate, coordinates [][]Coordinate) bool {
	return cor.row >= 0 && cor.row < len(coordinates) && cor.column >= 0 && cor.column < len(coordinates[0])
}

func getPath(startPos Coordinate, coordinates [][]Coordinate) []Coordinate {
	path := make([]Coordinate, 0)
	path = append(path, startPos)

	direction := UP
	currentPos := startPos
	for {
		// NB: Wack at de 2 siste verdiene starter som 0
		nextPos := Coordinate{currentPos.row, currentPos.column, 0, 0}
		fmt.Println("Current pos:", currentPos,
			"Next pos:", nextPos,
			"Direction:", direction)
		switch direction {
		case UP:
			nextPos.row--
		case RIGHT:
			nextPos.column++
		case DOWN:
			nextPos.row++
		case LEFT:
			nextPos.column--
		}
		if !coordinateIsWithinBounds(nextPos, coordinates) {
			fmt.Println(nextPos, " is out of bounds")
			break
		}
		nextPos.value = coordinates[nextPos.row][nextPos.column].value
		if nextPos.value == '#' {
			fmt.Println(nextPos, " is a wall")
			direction = getNextDirection(direction)
		} else {
			currentPos = nextPos
		}
		nextPos.visitCount++
		path = append(path, currentPos)
	}
	return path
}

func getUniqueCoordinatesInPath(path []Coordinate) []Coordinate {
	unique := make([]Coordinate, 0)
	for _, cor := range path {
		found := false
		for _, u := range unique {
			if cor.row == u.row && cor.column == u.column {
				found = true
				break
			}
		}
		if !found {
			unique = append(unique, cor)
		}
	}
	return unique
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	coordinates := readInput(scanner)
	fmt.Println(coordinates)
	fmt.Println("Rows:", len(coordinates))
	fmt.Println("Columns:", len(coordinates[0]))

	startPos := getStartPosition(coordinates)
	fmt.Println("Start position:", startPos)

	path := getPath(startPos, coordinates)
	fmt.Println("Path:", path)
	fmt.Println("Path len:", len(path))
	uniqueCoordinates := getUniqueCoordinatesInPath(path)

	printGrid(coordinates)

	printGridWithPath(coordinates, path)
	p1 := len(uniqueCoordinates)
	fmt.Println("Part 1:", p1)
}
