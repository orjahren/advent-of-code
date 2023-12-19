package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Rule struct {
	val, checkSign rune
	target         *Workflow
	targetName     string
	isRedirect     bool
	isAcceptance   bool
	isRejection    bool
}

type Workflow struct {
	rules     map[string]*Rule
	rulesList []Rule
	name      string
}

func getRuleFromString(ruleStr string) Rule {
	fmt.Println("ruleStr: ")
	fmt.Println(ruleStr)
	r := Rule{0, 0, nil, "", false, false, false}

	colSplit := strings.Split(ruleStr, ":")
	if len(colSplit) == 1 {
		if colSplit[0] == "R" {
			r.isRejection = true

		} else if colSplit[0] == "A" {
			r.isAcceptance = true
		} else {
			//panic("error with rule creation: " + colSplit[0])
		}
	} else {
		toParse := colSplit[0]
		fmt.Println("toParse: ")
		fmt.Println(toParse)
		fmt.Println("colSplit: ")
		fmt.Println(colSplit)
		r.targetName = colSplit[1]
		if strings.Contains(toParse, "<") {
			fmt.Println("toParse inneholder < ")
		} else if strings.Contains(toParse, ">") {
			fmt.Println("toParse inneholder < ")
		}
		checkSign := toParse[1]
		r.checkSign = rune(checkSign)
	}
	r.isRedirect = r.isAcceptance || r.isRejection
	fmt.Println("r: ")
	fmt.Println(r)
	return r
}

func workflowFromLine(line string) Workflow {
	stripped := strings.Trim(line, " \n}")
	fmt.Println("stripped: ")
	fmt.Println(stripped)
	spl := strings.Split(stripped, "{")
	fmt.Println("spl: ")
	fmt.Println(spl)
	name := spl[0]
	rulesStrs := strings.Split(spl[1], ",")
	fmt.Println("rulesStrs: ")
	fmt.Println(rulesStrs)
	rules := make([]Rule, 0)
	for _, ruleStr := range rulesStrs {
		rule := getRuleFromString(ruleStr)
		rules = append(rules, rule)
	}
	workflow := Workflow{make(map[string]*Rule), rules, name}
	fmt.Println("workflow: ")
	fmt.Println(workflow)
	return workflow
}

type Part struct {
	x, m, a, s int
}

func ruleIsValidForPart(rule Rule, part Part) bool {
	return true
}

func parsePartForLine(line string) Part {
	trimmed := strings.Trim(line, " \n{}")
	// remove all matches of chars

	fmt.Println("trimmed: ")
	fmt.Println(trimmed)
	spl := strings.Split(trimmed, ",")
	fmt.Println("spl: ")
	fmt.Println(spl)
	// cast to int
	ints := make([]int, 0)
	for _, char := range spl {
		parsed, _ := strconv.Atoi(char[2:])
		ints = append(ints, int(parsed))
	}
	fmt.Println("ints: ")
	fmt.Println(ints)
	return Part{ints[0], ints[1], ints[2], ints[3]}
}

func main() {
	file, _ := os.Open("example")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')

	workflows := make(map[string]*Workflow)
	workflowList := make([]*Workflow, 0)

	for line != "\n" {
		fmt.Println(line)
		workFlow := workflowFromLine(line)
		workflows[workFlow.name] = &workFlow
		workflowList = append(workflowList, &workFlow)
		line, _ = reader.ReadString('\n')

	}

	fmt.Println("------------")
	line, _ = reader.ReadString('\n')

	parts := make([]Part, 0)

	for line != "" {
		fmt.Println(line)
		part := parsePartForLine(line)
		parts = append(parts, part)
		line, _ = reader.ReadString('\n')
	}
}
