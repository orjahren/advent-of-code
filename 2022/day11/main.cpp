#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>

using ll = long long;

class Monkey
{
public:
    std::vector<ll> items;
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
    void inspectItem(ll &item, std::vector<Monkey *> *monkeys, int &itemIndex, int *pLoopCounter, ll &lcm, int &part)
    {
        item = this->getWorryLevel(item);
        if (part == 1)
        {
            item = floor(item / 3);
        }
        item %= lcm;
        monkeys->at(this->getThrowTargetId(item))->items.push_back(item);
        this->items.erase(this->items.begin() + itemIndex);
        (*pLoopCounter)--;
    }

private:
    int getThrowTargetId(ll &item)
    {
        return this->doTest(item) ? this->testTrueTarget : this->testFalseTarget;
    }
    bool doTest(ll &item)
    {
        return (item % this->testDivBy) == 0;
    }
    ll getWorryLevel(ll &item)
    {
        ll operand = opB;
        if (this->opFlag)
        {
            operand = item;
        }
        switch (opChar)
        {
        case '+':
            return item + operand;
        case '*':
            return item * operand;
        }
        return item / operand;
    }
};

std::vector<Monkey *> *readFileAndInitMonkeys(std::string *filename)
{
    std::string line;
    std::ifstream file(*filename);
    std::vector<Monkey *> *allMonkeys = new std::vector<Monkey *>;
    while (getline(file, line))
    {
        Monkey *m = new Monkey;
        allMonkeys->push_back(m);

        getline(file, line);
        line.erase(0, line.find(":") + 1);
        std::size_t commaIdx = line.find(",");
        while (commaIdx != 0)
        {
            commaIdx = line.find(",") + 1;
            std::string numStr = line.substr(0, commaIdx - 1);
            ll *item = new ll;
            *item = (ll)std::stoi(numStr);
            m->items.push_back(*item);
            line.erase(0, commaIdx); // Delete our handled item for the next iteration
        }

        // Deal with 'operation'
        getline(file, line); // Les opLine
        line.erase(0, line.find("d ") + 2);
        m->opChar = line[0];
        line.erase(0, 2); // delete the op and the space after
        if (line[0] == 'o')
        {
            m->opFlag = true;
        }
        else
        {
            m->opB = std::stoi(line);
        }

        // Deal with 'test'
        getline(file, line); // Les test-line
        line.erase(0, 21);   // Delete 'Test: divisible by'
        m->testDivBy = std::stoi(line);

        getline(file, line); // Les test-true
        line.erase(0, 29);   // Delete 'If true: throw to monkey'
        m->testTrueTarget = std::stoi(line);

        getline(file, line); // Les test-false
        line.erase(0, 30);   // Delete 'If false: throw to monkey'
        m->testFalseTarget = std::stoi(line);

        getline(file, line); // les inn en newline for å markere ny ape
    }
    return allMonkeys;
}

ll performSimulation(int part, std::vector<Monkey *> *monkeys, ll &lcm)
{
    int loop = (part == 2) ? 10000 : 20;
    const int nMonkeys = monkeys->size();
    for (int turn = 0; turn < loop; turn++)
    {
        for (int monkeyIdx = 0; monkeyIdx < nMonkeys; monkeyIdx++)
        {
            Monkey &m = *monkeys->at(monkeyIdx);
            m.inspectionCounter += m.items.size();
            for (int itemIdx = 0; itemIdx < m.items.size(); itemIdx++)
            {
                ll item = m.items.at(itemIdx);
                m.inspectItem(item, monkeys, itemIdx, &itemIdx, lcm, part);
            }
        }
    }
    ll counts[nMonkeys];
    for (int monkeyIdx = 0; monkeyIdx < nMonkeys; monkeyIdx++)
    {
        counts[monkeyIdx] = monkeys->at(monkeyIdx)->inspectionCounter;
    }
    std::sort(counts, counts + nMonkeys);
    return counts[nMonkeys - 1] * counts[nMonkeys - 2];
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

    ll res = performSimulation(1, monkeys, lcm);
    std::cout << "Part 1: " << res << std::endl;
    delete monkeys;
    monkeys = readFileAndInitMonkeys(&filename);
    res = performSimulation(2, monkeys, lcm);
    std::cout << "Part 2: " << res << std::endl;
}