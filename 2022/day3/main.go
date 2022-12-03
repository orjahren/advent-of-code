package main

import (
	"bufio"
	"fmt"
	"os"

	pq "github.com/emirpasic/gods/queues/priorityqueue"
	"github.com/emirpasic/gods/sets/hashset"
	"github.com/emirpasic/gods/utils"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

// Element is an entry in the priority queue
type Element struct {
	name     rune
	priority int
}

func byPriority(a, b interface{}) int {
	priorityA := a.(Element).priority
	priorityB := b.(Element).priority
	return -utils.IntComparator(priorityA, priorityB) // "-" descending order
}

func dealWithString(in string, out chan int) {

	var arrA []rune
	setB := hashset.New()
	len := len(in)
	for i, val := range in {
		if i < len/2 {
			arrA = append(arrA, val)
		} else {
			setB.Add(val)
		}
	}
	q := pq.NewWith(byPriority)
	for _, v := range arrA {
		if setB.Contains(v) {
			elt := Element{name: v, priority: int(v)}
			q.Enqueue(elt)
		}

	}

	pop, _ := q.Dequeue()
	lastSeen := pop.(Element).name

	var deduped []rune = []rune{lastSeen}

	for !q.Empty() {
		pop, _ = q.Dequeue()
		new := pop.(Element).name
		if new != lastSeen {
			deduped = append(deduped, new)
		}
		lastSeen = new
	}
	for _, val := range deduped {
		var pri rune

		if val < 97 {
			pri = val - 64 + 26
		} else {
			pri = val - 96
		}

		out <- int(pri)
	}
}

func main() {
	f, err := os.Open("input")
	check(err)
	defer f.Close()
	scanner := bufio.NewScanner(f)
	priorities := make(chan int)

	numberOfBlocks := 0
	for scanner.Scan() {
		go dealWithString(scanner.Text(), priorities)
		numberOfBlocks++
	}
	readBlocks := 0
	res := 0
	for true {
		res += <-priorities
		readBlocks++
		if readBlocks == numberOfBlocks {
			break
		}
	}
	fmt.Println("Part 1: ", res)
}
