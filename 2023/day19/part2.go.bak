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
	fmt.Println("ruleStr: ")
	fmt.Println(ruleStr)
	r := Rule{0, 0, 0, nil, "", false, false, false, false}

	colSplit := strings.Split(ruleStr, ":")
	if len(colSplit) == 1 {
		if colSplit[0] == "R" {
			r.isRejection = true
			fmt.Println("################# REJECTION")

		} else if colSplit[0] == "A" {
			fmt.Println("################# ACCEPTANCE")
			r.isAcceptance = true
		} else {
			//panic("error with rule creation: " + colSplit[0])
			fmt.Println("################# blind redirect")
			r.isBlindRedirect = true
			r.targetName = colSplit[0]
		}
	} else {
		toParse := colSplit[0]
		fmt.Println("toParse: ")
		fmt.Println(toParse)
		fmt.Println("colSplit: ")
		fmt.Println(colSplit)
		r.targetName = colSplit[1]
		var valSplit []string
		if strings.Contains(toParse, "<") {
			fmt.Println("toParse inneholder < ")
			valSplit = strings.Split(toParse, "<")
		} else if strings.Contains(toParse, ">") {
			fmt.Println("toParse inneholder < ")
			valSplit = strings.Split(toParse, ">")
		}
		parsedVal, _ := strconv.Atoi(valSplit[1])
		r.val = parsedVal
		checkSign := toParse[1]
		r.checkSign = rune(checkSign)
		r.checkChar = rune(toParse[0])
	}
	r.hasBool = r.isAcceptance || r.isRejection
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
	sumValue   int
}

func ruleIsValidForPart(rule Rule, part Part) bool {
	if rule.isBlindRedirect {
		return true
	}

	// TODO: Burde bruke hashmap for runes?
	if rule.checkSign == '<' {
		switch rule.checkChar {
		case 'x':
			return part.x < rule.val
		case 'm':
			return part.m < rule.val
		case 'a':
			return part.a < rule.val
		case 's':
			return part.s < rule.val
		default:
			panic("1 error with rule checkChar: " + string(rule.checkChar))
		}
	} else if rule.checkSign == '>' {
		switch rule.checkChar {
		case 'x':
			return part.x > rule.val
		case 'm':
			return part.m > rule.val
		case 'a':
			return part.a > rule.val
		case 's':
			return part.s > rule.val
		default:
			panic("2 error with rule checkChar: " + string(rule.checkChar))
		}

	} else {
		panic("3 error with rule checkSign: " + string(rule.checkSign))
	}
}

func getValueIfValid(workFlows []*Workflow, workFlowMap map[string]*Workflow, part Part) int {
	currentWorkflow := workFlowMap["in"]
	fmt.Println("currentWorkflow: ")
	fmt.Println(currentWorkflow)
	ruleIndex := 0

	currentRule := currentWorkflow.rulesList[ruleIndex]
	fmt.Println("currentRule: ")
	fmt.Println(currentRule)
	for !currentRule.hasBool {
		if ruleIsValidForPart(currentRule, part) {
			fmt.Println("rule is valid")
			ruleIndex = 0
			/*
				if currentRule.isBlindRedirect {
					//fmt.Println("rule is blind redirect, breaker")
					//break
					fmt.Println("rule is blind redirect")
				} else {
					currentWorkflow = currentRule.target
					currentRule = currentWorkflow.rulesList[ruleIndex]
				}
			*/
			fmt.Println("Will go from workflow: ")
			fmt.Println(currentWorkflow)
			fmt.Println("With rule: ")
			fmt.Println(currentRule)
			if currentRule.targetName == "A" {
				fmt.Println("currentRule.name == A")
				currentRule.hasBool = true
				currentRule.isAcceptance = true
			} else if currentRule.targetName == "R" {
				currentRule.hasBool = true
				currentRule.isRejection = true

			} else {

				currentWorkflow = currentRule.target
				fmt.Println("currentWorkflow: ")
				fmt.Println(currentWorkflow)
				currentRule = currentWorkflow.rulesList[ruleIndex]
				fmt.Println("Set current rule to next rule: ")
				fmt.Println(currentRule)
			}
		} else {
			fmt.Println("rule is NOT valid")
			ruleIndex++
			fmt.Println("ruleIndex: ")
			fmt.Println(ruleIndex)
			currentRule = currentWorkflow.rulesList[ruleIndex]
			fmt.Println("Set current rule to next rule: ")
			fmt.Println(currentRule)
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
	p := Part{ints[0], ints[1], ints[2], ints[3], 0}
	// set sum
	p.sumValue = p.x + p.m + p.a + p.s
	fmt.Println("p: ")
	fmt.Println(p)
	return p
}

func main() {
	//file, _ := os.Open("example")
	file, _ := os.Open("input")
	reader := bufio.NewReader(file)
	line, _ := reader.ReadString('\n')

	workflows := make(map[string]*Workflow)
	workflowList := make([]*Workflow, 0)
	allWorkflowNames := make([]string, 0)

	for line != "\n" {
		fmt.Println(line)
		trimmed := strings.Trim(line, " \n")
		if trimmed != "" {
			workFlow := workflowFromLine(trimmed)
			workflows[workFlow.name] = &workFlow
			workflowList = append(workflowList, &workFlow)
			allWorkflowNames = append(allWorkflowNames, workFlow.name)
		}
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

	// set targets for rules, for all workflow
	for _, workflow := range workflows {
		for i, rule := range workflow.rulesList {
			fmt.Println("rule.targetName: ")
			fmt.Println(rule.targetName)
			fmt.Println(workflows[rule.targetName])
			workflow.rulesList[i].target = workflows[rule.targetName]
			fmt.Println(workflows[rule.targetName])
		}

	}

	// print all names
	fmt.Println("------------ allWorkflowNames: ")
	fmt.Println(allWorkflowNames)

	part2 := 0
	for _, part := range parts {
		part2 += getValueIfValid(workflowList, workflows, part)
	}
	fmt.Println("part2: " + strconv.Itoa(part2))
}
