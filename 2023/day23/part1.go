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

func travrseRec(wg *sync.WaitGroup, currPath []Pos, grid [][]rune, pos, target Pos, ch chan int) {
	fmt.Println("traversing", pos)
	wg.Add(1)
	defer wg.Done()
	if isSamePos(pos, target) {
		println("found target!!")
		ch <- len(currPath)
		//wg.Done()
		return
	}

	if charIsArrow(grid[pos.x][pos.y]) {
		fmt.Print("arrow: ", pos, " ", string(grid[pos.x][pos.y]), " -> ")
		// we are at an arrow
		currPath = append(currPath, pos)
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
		travrseRec(wg, newPath, grid, pos, target, ch)
	} else {
		// we are at a junction
		currPath = append(currPath, pos)
		// go all ways except the way we came from
		for _, newPos := range []Pos{{pos.x, pos.y - 1}, {pos.x + 1, pos.y}, {pos.x, pos.y + 1}, {pos.x - 1, pos.y}} {
			// if !isSamePos(newPos, currPath[len(currPath)-1]) {
			if !hasVisitedThisPos(newPos, currPath) {
				fmt.Println("junction: ", pos, " -> ", newPos)
				if isSamePos(newPos, target) {
					println("found target!!")
					ch <- len(currPath)
					//wg.Done()
					return
				}
				if posIsOpen(newPos, grid) {
					fmt.Println("junction: ", pos, " -> ", newPos, " is open")
					newPath := make([]Pos, len(currPath))
					copy(newPath, currPath)
					travrseRec(wg, newPath, grid, newPos, target, ch)
				} else {
					//fmt.Println("junction: ", pos, " -> ", newPos, " is closed because newPos is ", string(grid[newPos.x][newPos.y]))
				}
			}
		}
	}
	//wg.Done()
}

func traverse(wg *sync.WaitGroup, grid [][]rune, startPos, endPos Pos, ch chan int) {
	currPath := make([]Pos, 0)
	currPath = append(currPath, startPos)
	wg.Add(1)
	travrseRec(wg, currPath, grid, startPos, endPos, ch)
	ch <- -1
	wg.Done()
	//close(ch)
}

func main() {
	file, _ := os.Open("example")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')
	println(line)
	lines := make([]string, 0)
	for line != "" {
		line = strings.Trim(line, "\n")
		lines = append(lines, line)
		line, _ = reader.ReadString('\n')
	}
	startPos := Pos{1, 0}
	// endPos is the position of the last character in the last line
	endPos := Pos{len(lines[0]) - 1, len(lines) - 1}
	println(lines[len(lines)-1])
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
	var wg sync.WaitGroup
	go traverse(&wg, grid, startPos, endPos, part1Ch)
	wg.Wait()
	// while ch is open
	for {
		select {
		case res := <-part1Ch:
			println("received result: ", res)
			if res != -1 {
				results = append(results, res)
			} else {
				part1Ch = nil
			}
		}
		if part1Ch == nil {
			break
		}
	}
	// print results
	fmt.Println("All results:")
	fmt.Println(results)
}
