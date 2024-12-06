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

var directions = []Direction{UP, RIGHT, DOWN, LEFT}

func getNextDirection(currentDirection Direction) Direction {
	for i, dir := range directions {
		if dir == currentDirection {
			//fmt.Println("Next direction:", directions[(i+1)%len(directions)])
			//println("Was:", currentDirection)
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
func printGridWithPathAndSpecial(coordinates [][]Coordinate, path []Coordinate, special Coordinate) {
	for _, row := range coordinates {
		for _, cor := range row {
			for _, p := range path {
				if special.row == p.row && special.column == p.column {
					fmt.Print("X")
					goto next
				}
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

func isCycle(path []CycleHack, ch CycleHack) bool {
	for i, p := range path {
		if ch.cor.row == p.cor.row && ch.cor.column == p.cor.column && ch.direction == p.direction {
			fmt.Println("Cycle detected at:", i, ch)
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
		// NB: Wack at de 2 siste verdiene starter som 0
		nextPos := Coordinate{currentPos.row, currentPos.column, currentPos.value, currentPos.visitCount}
		//fmt.Println("Current pos:", currentPos,
		//Next pos:", nextPos,
		//Direction:", direction)
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
		nextPos.visitCount++
		if !coordinateIsWithinBounds(nextPos, coordinates) {
			//mt.Println(nextPos, " is out of bounds")
			break
		}
		cyclePath = append(cyclePath, CycleHack{currentPos, direction})
		nextPos.value = coordinates[nextPos.row][nextPos.column].value
		if nextPos.value == '#' {
			//mt.Println(nextPos, " is a wall")
			direction = getNextDirection(direction)
		} else {
			currentPos = nextPos
			coordinates[currentPos.row][currentPos.column] = currentPos
		}
		if isCycle(cyclePath, CycleHack{currentPos, direction}) && isP2 {
			fmt.Println("Cycle detected")
			// TODO: Sjekke på p2 her?
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

func part2(grid [][]Coordinate) {
	p2 := -1
	exp := 0
	ch := make(chan Pair)
	startPos := getStartPosition(grid)

	for i, row := range grid {
		for j, cor := range row {
			if cor.value == '.' {
				fmt.Println("Will block:", cor)
				// copy grid
				exp++
				go func() {
					newGrid := make([][]Coordinate, len(grid))

					for i, row := range grid {
						newGrid[i] = make([]Coordinate, len(row))
						for j, inner := range row {
							newGrid[i][j] = Coordinate{inner.row, inner.column, inner.value, 0}
						}
					}
					newGrid[i][j].value = '#'
					path := getPath(startPos, newGrid, true)
					//mt.Println("Fant:", path)
					ch <- Pair{newGrid[i][j], path}
				}()
			} else {
				fmt.Println("Not blocking:", cor)
			}
		}
	}
	allPaths := make([][]Coordinate, exp)
	uniqueStartingPoints := make([]Coordinate, 0)
	for range exp {
		rep := <-ch
		fmt.Println(rep.block)
		if rep.path != nil {
			allPaths = append(allPaths, rep.path)
			fmt.Println("Blocked:", rep.block)
			fmt.Println("PL:", len(rep.path))
			uniqueStartingPoints = append(uniqueStartingPoints, rep.block)

			printGridWithPathAndSpecial(grid, rep.path, rep.block)
		} else {
			fmt.Println("For block:", rep.block, "no cyclic path found")
		}
	}
	fmt.Println("Num unique paths:", len(allPaths))
	fmt.Println("Num unique SP:", len(uniqueStartingPoints))

	fmt.Println("Part 2:", p2)
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	coordinates := readInput(scanner)
	fmt.Println(coordinates)
	fmt.Println("Rows:", len(coordinates))
	fmt.Println("Columns:", len(coordinates[0]))

	/*
		p1 := func() int {
			startPos := getStartPosition(coordinates)
			fmt.Println("Start position:", startPos)

			path := getPath(startPos, coordinates, false)
			uniqueCoordinates := getUniqueCoordinatesInPath(path)

			printGrid(coordinates)
			fmt.Println("Path:", path)
			fmt.Println("Path len:", len(path))

			printGridWithPath(coordinates, path)
			return len(uniqueCoordinates)
		}()
		fmt.Println("Part 1:", p1)
	*/

	part2(coordinates)
}
