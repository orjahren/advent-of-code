#include <iostream>
#include <unordered_map>
#include <fstream>
#include <deque>

#define LOG(x) std::cout << x << std::endl;

double useCharAsOp(double lx, char op, double rx)
{
    switch (op)
    {
    case '/':
        return lx / rx;
    case '+':
        return lx + rx;
    case '-':
        return lx - rx;
    case '*':
        return lx * rx;

    default:
        LOG("FANT IKKE CHAR")
        exit(1);
        break;
    }
}

bool isNumber(std::string &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (!std::isdigit(s.at(i)))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::unordered_map<std::string, double> hm;
    std::string line;
    // std::ifstream file("small");
    std::ifstream file("input");
    std::deque<std::string> q;

    while (getline(file, line))
    {
        q.push_back(line);
    }

    while (q.size() > 0)
    {
        std::string l = q.front(); // TODO: Burde være en referanse? Må poppe senere i så fall
        std::string orig = q.front();
        q.pop_front();
        LOG("L er: " << l)
        std::size_t cIdx = l.find(": ");
        LOG(cIdx)
        std::string var = l.substr(0, cIdx);
        std::string exp = l.substr(cIdx + 2);
        LOG(exp)
        LOG(var)
        if (isNumber(exp))
        {
            hm[var] = std::stoi(exp);
            LOG("\t\tConverterte " << exp << " til " << hm[var])
        }
        else
        {
            LOG("Exp som skal parses: " << exp)
            // Anta alle variabler har len(x) == 4
            std::string lop = exp.substr(0, 4);
            char op = exp.at(5);
            std::string rop = exp.substr(7);
            LOG("Lop op rop: " << lop << op << rop)

            if (hm.count(lop) && hm.count(rop))
            {
                double lx = hm[lop];
                double rx = hm[rop];
                if (var == "root")
                {
                    LOG(lx)
                    LOG(rx)
                }
                hm[var] = useCharAsOp(lx, op, rx);
            }
            else
            {
                q.push_back(orig);
            }
        }
    }
    std::cout << "Part 1: " << hm["root"] << std::endl;
}
