package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	reader.ReadString('\n')
	a, _ := reader.ReadString('\n')
	fmt.Println(a)
}
