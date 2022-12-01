package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
);

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func count(in []string, out chan int)  {

	tmpSum := 0;

	for _, val := range in {
		parsed, _ := strconv.Atoi(val);
		tmpSum += parsed;
	}

	out <- tmpSum;

}

func main() {
	 f, err := os.Open("input")
	 check(err);
	 defer f.Close();
	 scanner := bufio.NewScanner(f);
	blockCounts := make(chan int);

	 var block []string = make([]string, 10);
	numberOfBlocks := 0;
	 for scanner.Scan() {
		text := scanner.Text()
		if text == "" {
			go count(block, blockCounts);
			block = make([]string, 10);
			numberOfBlocks++;
		}else {
			block = append(block, text);
		}
	 }
	 max := -1;
	 for true {
		read := <- blockCounts;
		if(read > max) {
			max = read;
		}
		
		numberOfBlocks--;
		if(numberOfBlocks == 0) {
			break;
		}
	 }
	 fmt.Println("Part 1: ", max);

}