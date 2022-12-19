package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type Blueprint struct {
	recipe [][]int
}

type Tuple struct {
	time int
	bots int
	amt  int
}

func dfs(bp Blueprint, maxSpend []int, cache map[Tuple]int, time int, bots []int, amt []int, vChan chan int, iChan chan int, lineNumber int) int {
	if time == 0 {
		fmt.Println(amt)
		return amt[3]

	}

	key := Tuple{time, 0, 0}
	for i := 0; i < 4; i++ {
		fmt.Println("Getter bot", i)
		b := bots[i]
		if b != 0 {
			key.bots++
		}
	}
	for i := 0; i < 4; i++ {
		fmt.Println("Getter amt", i)
		a := amt[i]
		if a != 0 {
			key.amt++
		}
	}
	cacheVal, exists := cache[key]
	if exists {
		return cacheVal

	}
	fmt.Println("Encore")
	maxVal := amt[3] + bots[3]*time
	///
	// BOtTuype skal kun skulle kunne gå fra 0 - 3
	for botType := 0; botType < len(bp.recipe); botType++ {
		recipe := bp.recipe[botType]
		fmt.Println("Hentet recide: ", recipe)
		fmt.Println("SJakker maxSpend ", botType)
		if botType != 3 && bots[botType] >= maxSpend[botType] {
			continue
		}
		wait := 0
		rAmt := recipe[0]
		rType := recipe[1]
		fmt.Println("Fant bottype: ", bots[rType])
		if bots[rType] == 0 {
			break
		}
		wait = int(math.Max(float64(-(-(rAmt - amt[rType]) / bots[rType])), float64(wait)))
		if bots[rType] != 0 {
			remTime := time - wait - 1
			if remTime <= 0 {
				continue
			}
			bots_ := bots
			amt_ := make([]int, 4)
			for i := 0; i < len(bots); i++ {
				amt_[i] = amt[i] + bots[i]*(wait+1)
			}
			amt_[rType] -= rAmt
			bots_[botType]++

			for i := 0; i < 3; i++ {
				amt_[i] = int(math.Min(float64(amt_[i]), float64(maxSpend[i]*remTime)))
			}
			maxVal = int(math.Max(float64(maxVal), float64(dfs(bp, maxSpend, cache, remTime, bots_, amt_, vChan, iChan, lineNumber))))
		}
	}

	////
	cache[key] = maxVal
	vChan <- maxVal
	iChan <- lineNumber
	return maxVal

}

func check(err error) {
	if err != nil {
		panic(err)
	}
}

func main() {
	fmt.Println("Hello world")

	vChan := make(chan int)
	iChan := make(chan int)
	/*
		res := 0
	*/
	f, err := os.Open("small")
	check(err)

	scanner := bufio.NewScanner(f)

	exp, rErr := regexp.Compile("(\\d+) (\\w+)")
	check(rErr)

	dictToIndex := make(map[string]int)
	dictToIndex["ore"] = 0
	dictToIndex["clay"] = 1
	dictToIndex["obsidian"] = 2

	numberOfBluePrints := 0
	lineNumber := 0
	p1r := 0
	for scanner.Scan() {
		text := scanner.Text()
		var bp Blueprint
		match := exp.FindAllString(text, -1)
		fmt.Println(match)

		lineNumber++

		maxSpend := make([]int, 3)

		for i := 0; i < len(match); i += 1 {
			recipe := make([]int, 2)
			parts := strings.Split(match[i], " ")
			fmt.Println(parts)
			x, sErr := strconv.Atoi(parts[0])
			check(sErr)
			y := dictToIndex[parts[1]]
			fmt.Println(x, y)
			//recipe = append(recipe, x, y)
			recipe[0] = x
			recipe[1] = y
			maxSpend[y] = int(math.Max(float64(maxSpend[y]), float64(x)))
			bp.recipe = append(bp.recipe, recipe)
		}
		fmt.Println(bp)
		fmt.Println(maxSpend)
		numberOfBluePrints++
		botsArr := make([]int, 4)
		botsArr[0] = 1
		amtArr := make([]int, 4)
		fmt.Println("Starter DFS")
		v := dfs(bp, maxSpend, make(map[Tuple]int), 24, botsArr, amtArr, vChan, iChan, lineNumber)
		p1r += (lineNumber + 1) * v

	}
	/*
		res := 0
		for numberOfBluePrints > 0 {
			v := <-vChan
			i := <-iChan
			res += (i + 1) * v
			numberOfBluePrints--
		}
		fmt.Println("Part 1: ", res)
	*/
	fmt.Println("Part 1: ", p1r)
}
