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

type mapEntry struct {
	rangeStart int
	rangeEnd   int
	rangeSpan  int
}

type mapWrapper struct {
	entries []mapEntry
	name    string
}

func main() {
	println("Hello, World!")
	file, _ := os.Open("example")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')
	stripped := strings.TrimSpace(line)
	fmt.Println(stripped)

	fmt.Println("Starting loop.")
	currMap := make([]mapEntry, 0)
	allMaps := make([][]mapEntry, 0)
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		stripped := strings.TrimSpace(line)
		if stringContainsMap(stripped) {
			if len(currMap) > 1 {
				fmt.Println("currMap: ", currMap)
				allMaps = append(allMaps, currMap)
				fmt.Println("has length: ", len(currMap))
			}
			currMap = make([]mapEntry, 0)
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
			var me mapEntry
			me.rangeStart = parr[0]
			me.rangeEnd = parr[1]
			me.rangeSpan = parr[2]

			currMap = append(currMap, me)
			fmt.Println(stripped)

		}
	}
	allMaps = append(allMaps, currMap)
	fmt.Println(allMaps)
	fmt.Println(len(allMaps))
}
