#include <iostream>
#include <complex>
#include <set>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_set>

#define LOG(x) std::cout << x << std::endl;

bool vecContains(std::vector<std::complex<int>> &vec, std::complex<int> val)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec.at(i) == val)
        {
            return true;
        }
    }
    return false;
}

// Inspired by: https://github.com/hyper-neutrino/advent-of-code/blob/main/2022/day14p1.py
int main()
{
    int abyss = 0;
    // std::set<std::complex<int>> b;
    // std::unordered_set<std::complex<int> > b;
    std::vector<std::complex<int>> b;

    std::string line;
    // std::ifstream file("small");
    std::ifstream file("input");
    while (getline(file, line))
    {
        LOG("line: " << line)
        std::vector<std::pair<int, int>> vec;
        while (line.size() > 0)
        {
            std::size_t spx = line.find(" ");
            std::string coor = line.substr(0, spx);
            line.erase(0, spx + 4);
            if (coor[0] == ',')
            {
                continue;
            }
            LOG("coor: " << coor)
            std::size_t cix = coor.find(",");
            std::string a = coor.substr(0, cix);
            LOG("a:" << a)
            int x = std::stoi(a);
            coor.erase(0, cix + 1);
            int y = std::stoi(coor);
            std::pair<int, int> p = std::make_pair(x, y);
            vec.push_back(p);
        }
        LOG("Har prosessert linjen")
        for (int i = 0; i < vec.size() - 1; i++)
        {
            std::pair<int, int> &p1 = vec[i];
            std::pair<int, int> &p2 = vec[i + 1];

            LOG(p1.first << ", " << p2.first)

            // TODO: This can be optimized. Duplicate calculations
            int x1 = std::min(p1.first, p2.first);
            int x2 = std::max(p1.first, p2.first);

            int y1 = std::min(p1.second, p2.second);
            int y2 = std::max(p1.second, p2.second);

            for (int x = x1; x < x2 + 1; x++)
            {
                for (int y = y1; y < y2 + 1; y++)
                {
                    std::complex<int> c(x, y * 1);
                    // b.insert(c);
                    b.push_back(c);
                    abyss = std::max(abyss, y + 1);
                }
            }
        }
    }
    LOG("Har lest og inittet")

    int t = 0;

    while (true)
    {
        std::complex<int> s(500, 1);
        while (true)
        {
            if (std::imag(s) >= abyss)
            {
                std::cout << "Part 1: " << t << std::endl;
                return 0;
            }

            std::complex<int> y1(0, 1);
            std::complex<int> c1 = s + y1; //(s, 1);
            if (!vecContains(b, c1))
            {
                s += std::complex<int>(0, 1);
                continue;
            }
            if (!vecContains(b, c1 - 1))
            {
                s += std::complex<int>(0, 1) - 1;
                continue;
            }
            if (!vecContains(b, c1 + 1))
            {
                s += std::complex<int>(0, 1) + 1;
                continue;
            }
            b.push_back(s);
            t++;
            break;
        }
    }
}