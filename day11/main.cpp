#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define LOG(x) std::cout << x << std::endl;

double useCharAsArithmeticOperator(char op, int a, int b)
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

class Monkey
{
public:
    int id;
    std::vector<int> items;
    int opA;
    int opB;
    char opChar;
    int testDivBy;
    int testTrueTarget;
    int testFalseTarget;

    double getWorryLevel()
    {
        return 0; // EXEC OPERATION
    }
};

int main()
{

    std::cout << "Les monques seraient inittedé \n\n"
              << std::endl;
    std::string line;
    std::ifstream file("small");
    std::vector<Monkey *> allMonkeys;
    int monkeyIdCounter = 0;
    double worryLevel;
    while (getline(file, line))
    {
        std::cout << "******** Skal starte en ny ape: " << line << std::endl;
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
            LOG("Line er: " << line)

            commaIdx = line.find(",") + 1;
            LOG("KommaIdx er " << commaIdx)
            std::string numStr = line.substr(0, commaIdx - 1);
            // numStr = numStr.substr(0, numStr.find(","));
            LOG("Fant nr: " << numStr)
            int objId = std::stoi(numStr);
            m->items.push_back(objId);
            line.erase(0, commaIdx);
        }
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
        }
        else
        {
            m->opB = std::stoi(line);
        }
        LOG(line)
        // std::string opLine =

        // Deal with 'test'
        getline(file, line); // Les test-line
        getline(file, line); // Les test-true
        getline(file, line); // Les test-false

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