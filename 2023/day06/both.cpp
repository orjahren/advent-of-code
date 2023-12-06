#include <bits/stdc++.h>
typedef long long ll;
int nWinningOptions(ll timeLimit, ll competitor)
{
    int res = 0;
    for (int i = 1; i < timeLimit; i++)
        ((i * (timeLimit - i)) > competitor) && res++;
    return res;
}
int main()
{
    int part1 = 1;
    std::string inp;
    std::cin >> inp;
    std::vector<std::string> v(4);
    for (int i = 0; i < v.size(); i++)
        std::cin >> v[i];
    std::string time = accumulate(v.begin(), v.end(), std::string(""));
    std::cin >> inp;
    for (int i = 0; i < v.size(); i++)
    {
        std::cin >> inp;
        part1 *= nWinningOptions(stoll(v[i]), stoll(inp));
        v[i] = inp;
    }
    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << nWinningOptions(stoll(time), std::stoll(accumulate(v.begin(), v.end(), std::string("")))) << std::endl;
}