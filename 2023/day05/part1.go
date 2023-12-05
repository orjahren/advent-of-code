package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func stringContainsMap(s string) bool {
	return strings.Contains(s, "map")
}

type rangeEntry struct {
	rangeStart int
	rangeEnd   int
	rangeSpan  int
}

type aocMap struct {
	entries []rangeEntry
	name    string
	from    string
	to      string
}

func main() {
	println("Hello, World!")
	file, _ := os.Open("example")
	//file, _ := os.Open("input")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')
	stripped := strings.TrimSpace(line)
	seeds := make([]int, 0)
	split := strings.Split(stripped, " ")

	for i := range split {
		split[i] = strings.TrimSpace(split[i])
		parsed, _ := strconv.Atoi(split[i])
		if parsed > 0 {

			seeds = append(seeds, parsed)
		}
	}

	fmt.Println(stripped)
	fmt.Println(seeds)

	fmt.Println("Starting loop.")
	currRange := make([]rangeEntry, 0)
	allMaps := make([]aocMap, 0)
	var currMap aocMap
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		stripped := strings.TrimSpace(line)
		if stringContainsMap(stripped) {
			fmt.Println("new map found: " + stripped)
			if len(currRange) > 1 {
				fmt.Println("currMap: ", currRange)
				currMap = aocMap{currRange, stripped, "", ""}
				allMaps = append(allMaps, currMap)
				currMap = aocMap{}
				fmt.Println("has length: ", len(currRange))
			}
			currRange = make([]rangeEntry, 0)
			continue
		} else {
			spl := strings.Split(stripped, " ")
			fmt.Println("spl: ", spl)
			if len(spl) < 3 {
				continue
			}
			parr := make([]int, 3)

			for i := range spl {
				spl[i] = strings.TrimSpace(spl[i])
				parsed, _ := strconv.Atoi(spl[i])
				parr[i] = parsed
			}
			var me rangeEntry
			me.rangeStart = parr[0]
			me.rangeEnd = parr[1]
			me.rangeSpan = parr[2]
			fmt.Println("me:: ")
			fmt.Println(me)

			currRange = append(currRange, me)
			fmt.Println(stripped)

		}
	}
	allMaps = append(allMaps, currMap)
	fmt.Println(allMaps)
	fmt.Println(len(allMaps))
	fmt.Println(allMaps[0])
}
