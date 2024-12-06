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
}
type Pair struct {
	block Coordinate
	path  []Coordinate
}

type CycleHack struct {
	cor       Coordinate
	direction Direction
}
type Direction int

const (
	UP Direction = iota
	RIGHT
	DOWN
	LEFT
)

func getNextDirection(currentDirection Direction) Direction {
	var directions = []Direction{UP, RIGHT, DOWN, LEFT}
	for i, dir := range directions {
		if dir == currentDirection {
			return directions[(i+1)%len(directions)]
		}
	}
	panic("Unknown direction")
}

func lineToCor(line string, rowCount int) []Coordinate {
	spl := strings.Split(line, "")
	ret := make([]Coordinate, len(spl))
	for colIdx, x := range spl {
		c := Coordinate{rowCount, colIdx, rune(x[0])}
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

func coordinateIsWithinBounds(cor Coordinate, coordinates [][]Coordinate) bool {
	return cor.row >= 0 && cor.row < len(coordinates) && cor.column >= 0 && cor.column < len(coordinates[0])
}

func isCycle(path []CycleHack, ch CycleHack) bool {
	for _, p := range path {
		if ch.cor.row == p.cor.row && ch.cor.column == p.cor.column && ch.direction == p.direction {
			return true
		}
	}
	return false
}

func getPath(startPos Coordinate, coordinates [][]Coordinate, isP2 bool) []Coordinate {
	path := make([]Coordinate, 0)
	path = append(path, startPos)

	cyclePath := make([]CycleHack, 0)
	cyclePath = append(cyclePath, CycleHack{startPos, UP})

	direction := UP
	currentPos := startPos
	for {
		nextPos := Coordinate{currentPos.row, currentPos.column, currentPos.value}
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
			break
		}
		cyclePath = append(cyclePath, CycleHack{currentPos, direction})
		nextPos.value = coordinates[nextPos.row][nextPos.column].value
		if nextPos.value == '#' {
			direction = getNextDirection(direction)
		} else {
			currentPos = nextPos
			coordinates[currentPos.row][currentPos.column] = currentPos
		}
		if isCycle(cyclePath, CycleHack{currentPos, direction}) && isP2 {
			return path
		}
		path = append(path, currentPos)
	}
	if isP2 {
		return nil
	} else {
		return path
	}
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

func part2(startPos Coordinate, grid [][]Coordinate) int {
	exp := 0
	ch := make(chan Pair)
	for i, row := range grid {
		for j, cor := range row {
			if cor.value == '.' {
				exp++
				go func() {
					newGrid := make([][]Coordinate, len(grid))
					for i, row := range grid {
						newGrid[i] = make([]Coordinate, len(row))
						for j, inner := range row {
							newGrid[i][j] = Coordinate{inner.row, inner.column, inner.value}
						}
					}
					newGrid[i][j].value = '#'
					path := getPath(startPos, newGrid, true)
					ch <- Pair{newGrid[i][j], path}
				}()
			}
		}
	}
	p2 := 0
	for range exp {
		rep := <-ch
		if rep.path != nil {
			p2++
		}
	}
	return p2
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	coordinates := readInput(scanner)

	startPos := getStartPosition(coordinates)
	p1 := func() int {
		path := getPath(startPos, coordinates, false)
		uniqueCoordinates := getUniqueCoordinatesInPath(path)
		return len(uniqueCoordinates)
	}()
	fmt.Println("Part 1:", p1)

	p2 := part2(startPos, coordinates)
	fmt.Println("Part 2:", p2)
}
