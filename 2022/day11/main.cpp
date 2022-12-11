#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <math.h> //trengs for 'floor'

#define LOG(x) std::cout << x << std::endl;
#define LOG1(x) LOG("\t" << x)
#define LOG2(x) LOG("\t\t" << x)
#define LOG3(x) LOG("\t\t\t" << x)
#define LINEBREAK LOG1("-----")
#define STARBREAK LOG1("*****")

using ll = long long;

// https://stackoverflow.com/a/34944238/14530865
ll useCharAsArithmeticOperator(char &op, ll &a, ll &b)
{
    // LOG("SKal bruke denne operatoren: " << op)
    switch (op)
    {
    case '+':
        return a + b;
    case '*':
        return a * b;
    default:
        throw std::runtime_error("No such operator");
    }
}

class Item
{
public:
    int id;
    ll worryLevel;
};

class Monkey
{
public:
    int id;
    std::vector<Item *> items;
    ll opA;
    ll opB;
    char opChar;
    int testDivBy;
    int testTrueTarget;
    int testFalseTarget;
    bool opFlag;

    int inspectionCounter;

    Monkey()
    {
        this->opFlag = false;
        this->inspectionCounter = 0;
    }

    int getThrowTargetId(Item *item)
    {
        if (this->doTest(item))
        {
            return this->testTrueTarget;
        }
        else
        {
            return this->testFalseTarget;
        }
    }

    void inspectItem(Item *item, std::vector<Monkey *> *monkeys, int &itemIndex, int *pLoopCounter, ll lcm)
    {
        item->worryLevel = this->getWorryLevel(item);
        item->worryLevel %= lcm;
        int throwTargetId = this->getThrowTargetId(item);
        Monkey &throwTarget = *monkeys->at(throwTargetId);
        throwTarget.items.push_back(item);
        this->items.erase(this->items.begin() + itemIndex);
        (*pLoopCounter)--;
    }

private:
    bool doTest(Item *item)
    {
        return (item->worryLevel % this->testDivBy) == 0;
    }
    ll getWorryLevel(Item *item)
    {
        if (this->opFlag)
        {
            return useCharAsArithmeticOperator(opChar, item->worryLevel, item->worryLevel);
        }
        else
        {
            return useCharAsArithmeticOperator(opChar, item->worryLevel, opB);
        }
    }
};

std::vector<Monkey *> *readFileAndInitMonkeys(std::string *filename)
{
    LOG("Les monques seraient inittedé\n")
    std::string line;
    std::ifstream file(*filename);
    std::vector<Monkey *> *allMonkeys = new std::vector<Monkey *>;
    int monkeyIdCounter = 0;
    int itemIdCounter = 0;
    while (getline(file, line))
    {
        LOG("******** Skal starte en ny ape: " << line)
        Monkey *m = new Monkey;
        allMonkeys->push_back(m);
        m->id = monkeyIdCounter++;

        // Deal with 'initial items'
        LOG("\tFikser Initil items")
        getline(file, line);
        std::size_t colIdx = line.find(":") + 1;
        line.erase(0, colIdx);
        std::size_t commaIdx = line.find(",");
        while (commaIdx != 0)
        {
            Item *item = new Item;
            LOG("Line er: " << line)
            commaIdx = line.find(",") + 1;
            LOG("KommaIdx er " << commaIdx)
            std::string numStr = line.substr(0, commaIdx - 1);
            LOG("Fant nr: " << numStr)
            int worryLevel = std::stoi(numStr);

            item->worryLevel = worryLevel;
            item->id = itemIdCounter++;
            m->items.push_back(item);
            line.erase(0, commaIdx); // Delete our handled item for the next iteration
        }
        LINEBREAK

        // Deal with 'operation'
        LOG("\tFikser operation")
        getline(file, line); // Les opLine
        std::size_t opIdx = line.find("d ") + 2;
        line.erase(0, opIdx);
        char op = line[0];
        m->opChar = op;
        line.erase(0, 2); // delete the op and the space after
        if (line[0] == 'o')
        {
            m->opFlag = true;
        }
        else
        {
            m->opB = std::stoi(line);
        }
        LINEBREAK

        // Deal with 'test'
        LOG1("Fikser test")
        getline(file, line); // Les test-line
        line.erase(0, 21);   // Delete 'Test: divisible by'
        int testDivBy = std::stoi(line);
        m->testDivBy = testDivBy;
        LOG("Kun tallet:")
        LOG(line)

        getline(file, line); // Les test-true
        line.erase(0, 29);   // Delete 'If true: throw to monkey'
        int monkeTrue = std::stoi(line);
        m->testTrueTarget = monkeTrue;
        LOG("true monke id:" << line)

        getline(file, line); // Les test-false
        line.erase(0, 30);   // Delete 'If false: throw to monkey'
        int monkeFalse = std::stoi(line);
        LOG("False monke id:" << line)
        m->testFalseTarget = monkeFalse;

        // Just get a newline
        getline(file, line); // les inn en newline for å markere ny ape

        LOG("------------ Ape ferdig \n")
    }
    return allMonkeys;
}

int main()
{
    std::string filename = "input";
    std::vector<Monkey *> *monkeys = readFileAndInitMonkeys(&filename);

    ll lcm = 1;
    for (int monkeyIdx = 0; monkeyIdx < monkeys->size(); monkeyIdx++)
    {
        Monkey &m = *monkeys->at(monkeyIdx);
        lcm *= m.testDivBy;
    }
    LOG("lcm er " << lcm)

    for (int turn = 0; turn < 10000; turn++)
    {

        for (int monkeyIdx = 0; monkeyIdx < monkeys->size(); monkeyIdx++)
        {
            Monkey &m = *monkeys->at(monkeyIdx);
            m.inspectionCounter += m.items.size();
            for (int itemIdx = 0; itemIdx < m.items.size(); itemIdx++)
            {
                Item &item = *m.items.at(itemIdx);
                m.inspectItem(&item, monkeys, itemIdx, &itemIdx, lcm);
            }
        }
    }

    std::vector<ll> counts;
    for (int monkeyIdx = 0; monkeyIdx < monkeys->size(); monkeyIdx++)
    {
        Monkey &m = *monkeys->at(monkeyIdx);
        int mCount = m.inspectionCounter;
        counts.push_back(mCount);
        LOG("Monkey " << monkeyIdx << " inspected items " << mCount << " times.")
    }
    std::sort(counts.begin(), counts.end());
    int nMonkeys = monkeys->size();
    ll part2Res = counts.at(nMonkeys - 1) * counts.at(nMonkeys - 2);
    // LOG("Part 1: " << part1Res)
    LOG("Part 2: " << part2Res)
}