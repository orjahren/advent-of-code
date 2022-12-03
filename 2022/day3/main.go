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

// Comparator function (sort by element's priority value in descending order)
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
		//fmt.Println("Skal deale med ", val, "(", string(val), ")")
		if i < len/2 {
			arrA = append(arrA, val)
		} else {
			setB.Add(val)
		}
	}

	q := pq.NewWith(byPriority)

	for _, v := range arrA {
		//fmt.Println("Skal sjekke disse for en match:")
		//fmt.Println(k, string(v))

		if setB.Contains(v) {
			elt := Element{name: v, priority: int(v)}
			//fmt.Println("Skal enqueue", elt)
			q.Enqueue(elt)
		}

	}

	//fmt.Println("Etter loopen")
	pop, _ := q.Dequeue()
	//fmt.Println("tmp:", tmp)
	//lastSeen := reflect.ValueOf(tmp).FieldByName("priority").Interface().(rune)
	lastSeen := pop.(Element).name
	//fmt.Println("Første val er ", lastSeen)

	var deduped []rune = []rune{lastSeen}

	// deduplicate
	for !q.Empty() {
		pop, _ := q.Dequeue()
		fmt.Println(pop)
		new := pop.(Element).name
		if new != lastSeen {
			deduped = append(deduped, new)
		}
		lastSeen = new
	}
	fmt.Println("Deduped: ", deduped)
	// finn priorities for alt i dedpued -> send det over kanalen
	for _, val := range deduped {
		fmt.Println("Skal finne priority for ", val, string(val))
		var pri rune

		if val < 97 {
			pri = val - 64 + 26
		} else {
			pri = val - 96
		}

		fmt.Println("pri er ", pri)
		out <- int(pri)
	}
}

func main() {
	f, err := os.Open("input")
	// f, err := os.Open("small")
	check(err)
	defer f.Close()
	scanner := bufio.NewScanner(f)
	priorities := make(chan int)

	numberOfBlocks := 0
	for scanner.Scan() {
		text := scanner.Text()
		fmt.Println("har lest dette:", text)
		//go dealWithString(text, priorities)
		go dealWithString(text, priorities)
		numberOfBlocks++
	}
	readBlocks := 0
	res := 0
	for true {
		read := <-priorities
		res += read
		fmt.Println("Leste:", read)
		readBlocks++
		if readBlocks == numberOfBlocks {
			break
		}
	}
	fmt.Println("Part 1: ", res)
}
