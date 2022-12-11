#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define LOG(x) std::cout << x << std::endl;
#define LOG1(x) LOG("\t" << x)
#define LINEBREAK LOG1("-----")

// https://stackoverflow.com/a/34944238/14530865
double useCharAsArithmeticOperator(char &op, int &a, int &b)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        throw std::runtime_error("No such operator");
    }
}

class Item
{
public:
    int id;
    int worryLevel;
};

class Monkey
{
public:
    int id;
    std::vector<Item *> items;
    int opA;
    int opB;
    char opChar;
    int testDivBy;
    int testTrueTarget;
    int testFalseTarget;
    bool opFlag;

    Monkey()
    {
        this->opFlag = false;
    }

    double getWorryLevel(Item *item)
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

void inspectItem(Monkey *m, Item *item)
{
    item->worryLevel = m->getWorryLevel(item);
}

int main()
{

    LOG("Les monques seraient inittedé\n")
    std::string line;
    std::ifstream file("small");
    std::vector<Monkey *> allMonkeys;
    int monkeyIdCounter = 0;
    int itemIdCounter = 0;
    double worryLevel;
    while (getline(file, line))
    {
        LOG("******** Skal starte en ny ape: " << line)
        Monkey *m = new Monkey;
        allMonkeys.push_back(m);
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
            // numStr = numStr.substr(0, numStr.find(","));
            LOG("Fant nr: " << numStr)
            int worryLevel = std::stoi(numStr);

            item->worryLevel = worryLevel;
            item->id = itemIdCounter++;
            m->items.push_back(item);
            line.erase(0, commaIdx); // Delete our handled item for the next iteration
        }
        LINEBREAK
        // LOG("Line etter loopen: " << line)
        //  LOG(numStr) // gir riktig

        // Deal with 'operation'
        LOG("\tFikser operation")
        getline(file, line); // Les opLine
        std::size_t opIdx = line.find("d ") + 2;
        line.erase(0, opIdx);
        char op = line[0];
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
    /*
    for (Monkey *m : allMonkeys)
    {
        LOG("Frir opp minne for monke " << m->id)
        delete m;
    }
    LOG(allMonkeys.size())
    */
}