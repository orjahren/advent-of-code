#include <iostream>
#include <unordered_map>
#include <fstream>
#include <deque>

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
    default:
        return lx * rx;
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
    std::ifstream file("input");
    std::deque<std::string> q;
    while (getline(file, line))
    {
        q.push_back(line);
    }

    while (q.size() > 0)
    {
        std::string &l = q.front();
        std::string var = l.substr(0, 4);
        std::string exp = l.substr(6);
        if (isNumber(exp))
        {
            hm[var] = std::stoi(exp);
        }
        else
        {
            std::string lop = exp.substr(0, 4);
            std::string rop = exp.substr(7);
            if (hm.count(lop) && hm.count(rop))
            {
                hm[var] = useCharAsOp(hm[lop], exp.at(5), hm[rop]);
            }
            else
            {
                q.push_back(l);
            }
        }
        q.pop_front();
    }
    std::cout << "Part 1: " << std::setprecision(20) << hm["root"] << std::endl;
}
