package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func convertToDecimal(snafu string, ch chan int) {
	for i := len(snafu) - 1; i >= 0; i-- {
		var val int
		if snafu[i] == '-' {
			val = -1
		} else if snafu[i] == '=' {
			val = -2
		} else {
			val = int(snafu[i] - '0')
		}
		ch <- val * int(math.Pow(5, float64(len(snafu)-i-1)))
	}
}

func main() {
	f, err := os.Open("input")
	defer f.Close()
	check(err)
	scanner := bufio.NewScanner(f)
	ch := make(chan int)
	nExpect := 0
	for scanner.Scan() {
		line := scanner.Text()
		nExpect += len(line)
		go convertToDecimal(line, ch)
	}

	toBeConv := 0
	for nExpect > 0 {
		toBeConv += <-ch
		nExpect--
	}

	fmt.Println("To be conv:", toBeConv)

	var chars [5]rune = [5]rune{'=', '-', '0', '1', '2'}
	arr := make([]rune, 20)
	for toBeConv != 0 {
		pf := toBeConv + 2
		toBeConv = pf / 5
		arr = append(arr, chars[pf%5])

	}
	rev := make([]rune, len(arr)+1)
	for i := len(arr) - 1; i >= 0; i-- {
		rev[len(arr)-i] = arr[i]
	}
	res := string(rev)
	fmt.Println("Part 1:", res)
}
