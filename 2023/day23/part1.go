package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"sync"
)

type Pos struct {
	x, y int
}

func posIsOpen(pos Pos, grid [][]rune) bool {
	if pos.x < 0 || pos.y < 0 || pos.x >= len(grid) || pos.y >= len(grid[0]) {
		return false
	}
	//fmt.Println(pos, grid[pos.x][pos.y])
	return grid[pos.x][pos.y] != '#'
}

func charIsArrow(c rune) bool {
	return c == '^' || c == '>' || c == 'v' || c == '<'
}

func isSamePos(a, b Pos) bool {
	return a.x == b.x && a.y == b.y
}

func hasVisitedThisPos(pos Pos, path []Pos) bool {
	for _, p := range path {
		if isSamePos(p, pos) {
			return true
		}
	}
	return false
}

func travrseRec(wg *sync.WaitGroup, currPath []Pos, grid [][]rune, pos, target Pos, ch chan int, pathCh chan []Pos) {
	fmt.Println("traversing", pos)
	wg.Add(1)
	//defer wg.Done()
	if isSamePos(pos, target) {
		println("\t\t\t found target!!")
		ch <- len(currPath)
		pathCh <- currPath
		//wg.Done()
		return
	}
	if hasVisitedThisPos(pos, currPath) {
		fmt.Println("already visited ", pos)
		return
	}
	currPath = append(currPath, pos)

	if charIsArrow(grid[pos.x][pos.y]) {
		fmt.Print("arrow: ", pos, " ", string(grid[pos.x][pos.y]), " -> ")
		// we are at an arrow
		switch grid[pos.x][pos.y] {
		case '^':
			pos.y--
		case '>':
			pos.x++
		case 'v':
			pos.y++
		case '<':
			pos.x--
		}
		fmt.Println(pos)
		newPath := make([]Pos, len(currPath))
		copy(newPath, currPath)
		travrseRec(wg, newPath, grid, pos, target, ch, pathCh)
	} else {
		// we are at a junction
		// go all ways except the way we came from
		for _, newPos := range []Pos{{pos.x, pos.y - 1}, {pos.x + 1, pos.y}, {pos.x, pos.y + 1}, {pos.x - 1, pos.y}} {
			fmt.Println("junction: ", pos, " -> ", newPos)
			if isSamePos(newPos, target) {

				/*
					println("\t\t\t hack: found target!!")
					ch <- len(currPath) + 1
					pathCh <- append(currPath, newPos)
					//wg.Done()
					return
				*/

			}
			if posIsOpen(newPos, grid) {
				fmt.Println("junction: ", pos, " -> ", newPos, " is open")
				travrseRec(wg, currPath, grid, newPos, target, ch, pathCh)
				//return
			}
		}
	}
}

func traverse(wg *sync.WaitGroup, grid [][]rune, startPos, endPos Pos, ch chan int, pathCh chan []Pos) {
	currPath := make([]Pos, 0)
	fmt.Println("waiting for traverse to finish")
	travrseRec(wg, currPath, grid, startPos, endPos, ch, pathCh)
	fmt.Println("traverse finished")
	close(pathCh)
	close(ch)
}

func getGridWithPath(grid [][]rune, path []Pos) [][]rune {
	newGrid := make([][]rune, len(grid))
	for i, line := range grid {
		newGrid[i] = make([]rune, len(line))
		copy(newGrid[i], line)
	}
	for _, pos := range path {
		newGrid[pos.y][pos.x] = 'O'
	}
	return newGrid

}

func drawGrid(grid [][]rune) {
	for _, line := range grid {
		for _, c := range line {
			print(string(c))
		}
		println()
	}
}

func getLines(fileName string) []string {
	file, _ := os.Open(fileName)
	defer file.Close()
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')
	println(line)
	lines := make([]string, 0)
	for line != "" {
		line = strings.Trim(line, "\n")
		lines = append(lines, line)
		line, _ = reader.ReadString('\n')
	}
	return lines
}

func main() {
	lines := getLines("example")
	startPos := Pos{1, 0}
	// endPos is the position of the last character in the last line
	endPos := Pos{len(lines[0]) - 2, len(lines) - 1}
	println(lines[len(lines)-1])
	println(len(lines[len(lines)-1]))
	println(lines[len(lines)-1][len(lines[0])-2])
	fmt.Println(startPos, endPos)

	part1Ch := make(chan int)
	// convert lines to grid of runes
	grid := make([][]rune, len(lines))
	for i, line := range lines {
		grid[i] = make([]rune, len(line))
		for j, c := range line {
			grid[i][j] = c
		}
	}
	fmt.Println(grid)

	results := make([]int, 0)
	allPaths := make([][]Pos, 0)
	pathCh := make(chan []Pos)

	hackCh := make(chan int)
	var wg sync.WaitGroup
	wg.Add(1)
	go func() {
		println("starter anonym venting ")
		<-hackCh
		println(" anonym venting er ferdig")
		for res := range part1Ch {
			println("received result: ", res)
			results = append(results, res)
			path := <-pathCh
			allPaths = append(allPaths, path)
		}
		fmt.Println("part1Ch is closed")
		hackCh <- 1
	}()
	traverse(&wg, grid, startPos, endPos, part1Ch, pathCh)
	hackCh <- 1
	fmt.Println("traverse har returnert")
	<-hackCh
	// while ch is open
	// print results
	fmt.Println("All results:")
	fmt.Println(results)

	if len(results) > 0 {
		pathToShow := allPaths[0]
		println("\n")
		println("A path of length ", len(pathToShow), " is:")
		drawGrid(getGridWithPath(grid, pathToShow))
	}
}
