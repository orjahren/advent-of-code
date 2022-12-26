#include <iostream>
#include <string>
#include <fstream>
#include <deque>

using ll = long long;

ll convertToDecimal(std::string snafu)
{
    ll res = 0;
    for (int i = snafu.size() - 1; i >= 0; i--)
    {
        char c = snafu.at(i);
        int val;
        if (c == '-')
        {
            val = -1;
        }
        else if (c == '=')
        {
            val = -2;
        }
        else
        {
            val = c - '0';
        }
        ll tmp = 1;
        for (int j = 0; j < snafu.size() - i - 1; j++)
        {
            tmp *= 5;
        }
        res += val * tmp;
    }
    return res;
}

int main()
{
    std::string line;
    std::ifstream file("input");
    ll toBeConv = 0;
    while (getline(file, line))
    {
        toBeConv += convertToDecimal(line);
    }
    std::string str = std::to_string(toBeConv);
    std::deque<char> q;
    char chars[5] = {'=', '-', '0', '1', '2'};
    std::string res;
    while (toBeConv != 0)
    {
        ll pf = toBeConv + 2;
        toBeConv = pf / 5;
        res.insert(0, 1, chars[pf % 5]);
    }
    std::cout << "Part 1: " << res << std::endl;
}