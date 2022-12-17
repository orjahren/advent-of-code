#include <iostream>
#include <set>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <multiset>

#define LOG(x) std::cout << x << std::endl;

bool vecContains(std::vector<std::pair<int, int>> &vec, std::pair<int, int> val)
{
    return std::binary_search(vec.begin(), vec.end(), val);
}

// Inspired by: https://github.com/hyper-neutrino/advent-of-code/blob/main/2022/day14p1.py
int main()
{
    int abyss = 0;
    // std::set<std::pair<int, int>> b;
    // std::unordered_set<std::pair<int, int> > b;
    std::vector<std::pair<int, int>> b;

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
                    std::pair<int, int> c = std::make_pair(x, y);
                    // b.insert(c);
                    b.push_back(c);
                    abyss = std::max(abyss, y + 1);
                }
            }
        }
    }
    LOG("Har lest og inittet")
    LOG("sorterer vec")
    std::sort(b.begin(), b.end());
    LOG("sorterert ferdig")
    int t = 0;

    while (true)
    {
        std::pair<int, int> s = std::make_pair(500, 1);
        // LOG("Ytre")
        while (true)
        {
            // LOG("Indre")
            if (s.second >= abyss)
            {
                std::cout << "Part 1: " << t << std::endl;
                return 0;
            }

            if (!vecContains(b, std::make_pair(s.first, s.second + 1)))
            {
                s.second++;
                continue;
            }
            if (!vecContains(b, std::make_pair(s.first - 1, s.second + 1)))
            {
                s.second++;
                s.first--;
                continue;
            }
            if (!vecContains(b, std::make_pair(s.first + 1, s.second + 1)))
            {
                s.first++;
                s.second++;
                continue;
            }
            b.push_back(s);

            LOG("inserter ")
            std::sort(b.begin(), b.end());
            auto it = std::upper_bound(b.cbegin(), b.cend(), s);
            b.insert(it, s);
            LOG("har insertet ")
            t++;
            break;
        }
    }
}
