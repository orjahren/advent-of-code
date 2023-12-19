package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Rule struct {
	checkSign, checkChar rune
	val                  int
	target               *Workflow
	targetName           string
	isBlindRedirect      bool
	hasBool              bool
	isAcceptance         bool
	isRejection          bool
}

type Workflow struct {
	rules     map[string]*Rule
	rulesList []Rule
	name      string
}

func getRuleFromString(ruleStr string) Rule {
	r := Rule{0, 0, 0, nil, "", false, false, false, false}
	colSplit := strings.Split(ruleStr, ":")
	if len(colSplit) == 1 {
		if colSplit[0] == "R" {
			r.isRejection = true

		} else if colSplit[0] == "A" {
			// TODO: This doesnt work
			r.isAcceptance = true
		} else {
			r.isBlindRedirect = true
			r.targetName = colSplit[0]
		}
	} else {
		toParse := colSplit[0]
		r.targetName = colSplit[1]
		var valSplit []string
		if strings.Contains(toParse, "<") {
			valSplit = strings.Split(toParse, "<")
		} else if strings.Contains(toParse, ">") {
			valSplit = strings.Split(toParse, ">")
		}
		parsedVal, _ := strconv.Atoi(valSplit[1])
		r.val = parsedVal
		checkSign := toParse[1]
		r.checkSign = rune(checkSign)
		r.checkChar = rune(toParse[0])
	}
	r.hasBool = r.isAcceptance || r.isRejection
	return r
}

func workflowFromLine(line string) Workflow {
	stripped := strings.Trim(line, " \n}")
	spl := strings.Split(stripped, "{")
	name := spl[0]
	rulesStrs := strings.Split(spl[1], ",")
	rules := make([]Rule, 0)
	for _, ruleStr := range rulesStrs {
		rule := getRuleFromString(ruleStr)
		rules = append(rules, rule)
	}
	workflow := Workflow{make(map[string]*Rule), rules, name}
	return workflow
}

type Part struct {
	sumValue int
	vals     map[rune]int
}

func ruleIsValidForPart(rule Rule, part Part) bool {
	if rule.isBlindRedirect {
		return true
	}
	if rule.checkSign == '<' {
		return part.vals[rule.checkChar] < rule.val
	}
	return part.vals[rule.checkChar] > rule.val
}

func getValueIfValid(workFlowMap map[string]*Workflow, part Part) int {
	currentWorkflow := workFlowMap["in"]
	ruleIndex := 0
	currentRule := currentWorkflow.rulesList[ruleIndex]
	for !currentRule.hasBool {
		if ruleIsValidForPart(currentRule, part) {
			ruleIndex = 0
			if currentRule.targetName == "A" {
				currentRule.hasBool = true
				currentRule.isAcceptance = true
			} else if currentRule.targetName == "R" {
				currentRule.hasBool = true
				currentRule.isRejection = true
			} else {
				currentWorkflow = currentRule.target
				currentRule = currentWorkflow.rulesList[ruleIndex]
			}
		} else {
			ruleIndex++
			currentRule = currentWorkflow.rulesList[ruleIndex]
		}
	}
	if currentRule.isAcceptance {
		return part.sumValue
	} else {
		return 0
	}
}

func parsePartForLine(line string) Part {
	trimmed := strings.Trim(line, " \n{}")
	spl := strings.Split(trimmed, ",")
	ints := make([]int, 0)
	p := Part{0, make(map[rune]int)}
	for _, char := range spl {
		parsed, _ := strconv.Atoi(char[2:])
		p.vals[rune(char[0])] = parsed
		p.sumValue += parsed
		ints = append(ints, parsed)
	}
	return p
}

func main() {
	//file, _ := os.Open("example")
	file, _ := os.Open("input")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')

	workflows := make(map[string]*Workflow)

	for line != "\n" {
		trimmed := strings.Trim(line, " \n")
		if trimmed != "" {
			workFlow := workflowFromLine(trimmed)
			workflows[workFlow.name] = &workFlow
		}
		line, _ = reader.ReadString('\n')

	}
	line, _ = reader.ReadString('\n')
	parts := make([]Part, 0)
	for line != "" {
		part := parsePartForLine(line)
		parts = append(parts, part)
		line, _ = reader.ReadString('\n')
	}

	for _, workflow := range workflows {
		for i, rule := range workflow.rulesList {
			workflow.rulesList[i].target = workflows[rule.targetName]
		}
	}
	part1 := 0
	for _, part := range parts {
		part1 += getValueIfValid(workflows, part)
	}
	fmt.Println("part1: ", part1)
}
