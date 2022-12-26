#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <deque>

#define LOG(x) std::cout << x << std::endl;
using ll = long long;

std::string convertToSNAFU(ll val)
{
    std::string str = std::to_string(val);
    std::deque<char> q;
    ll tmp = val;
    std::string chars("=-012");
    while (tmp != 0)
    {
        ll div = floor((tmp + 2) / 5);
        int idx = (tmp + 2) % 5;
        tmp = div;
        q.push_front(chars.at(idx));
    }
    std::string res;
    while (q.size() > 0)
    {
        char c = q.front();
        res.push_back(c);
        q.pop_front();
    }
    return res;
}

ll convertToInt(std::string snafu)
{
    ll res = 0;
    for (int i = snafu.size() - 1; i >= 0; i--)
    {
        char c = snafu.at(i);
        int pos = snafu.size() - i - 1;
        int val = c - '0';
        if (c == '-')
        {
            val = -1;
        }
        else if (c == '=')
        {
            val = -2;
        }
        ll cal = val * pow(5, pos);
        res += cal;
    }
    return res;
}

int main()
{
    std::cout << "Hello world" << std::endl;
    std::string line;
    // std::ifstream file("small");
    std::ifstream file("input");

    std::vector<int> nums;
    ll toBeConv = 0;
    while (getline(file, line))
    {
        std::cout << line << " -> ";
        ll num = convertToInt(line);
        nums.push_back(num);
        std::cout << num << std::endl;
        toBeConv += num;
    }
    LOG("To be converted to SNAFU: " << toBeConv)
    std::string conv = convertToSNAFU(toBeConv);
    LOG("Part 1: " << conv)
}