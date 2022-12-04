package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"

	"github.com/emirpasic/gods/trees/binaryheap"
	"github.com/emirpasic/gods/utils"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func count(in []string, out chan int) {

	tmpSum := 0

	for _, val := range in {
		parsed, _ := strconv.Atoi(val)
		tmpSum += parsed
	}

	out <- tmpSum

}

func main() {
	f, err := os.Open("../input")
	check(err)
	defer f.Close()
	scanner := bufio.NewScanner(f)
	blockCounts := make(chan int)

	var block []string = make([]string, 10)
	numberOfBlocks := 0
	for scanner.Scan() {
		text := scanner.Text()
		if text == "" {
			go count(block, blockCounts)
			block = make([]string, 10)
			numberOfBlocks++
		} else {
			block = append(block, text)
		}
	}
	max := -1
	inverseIntComparator := func(a, b interface{}) int {
		return -utils.IntComparator(a, b)
	}
	heap := binaryheap.NewWith(inverseIntComparator)
	readBlocks := 0
	allElves := make([]int, numberOfBlocks)
	for true {
		read := <-blockCounts
		if read > max {
			max = read
		}
		// TODO: Fix heap-based solution
		heap.Push(read)
		allElves = append(allElves, read)

		readBlocks++
		if readBlocks == numberOfBlocks {
			break
		}
	}
	fmt.Println("Part 1: ", max)
	sort.Slice(allElves, func(i, j int) bool {
		return allElves[i] > allElves[j]
	})
	part2Res := allElves[0] + allElves[1] + allElves[2]

	/*
		for  i, val := range heap.Values() {
			fmt.Println(i,val)
			part2Res += val.(int);
			if (i == 2) {
				break;
			}
		 }
	*/
	fmt.Println("Part 2: ", part2Res)

}
