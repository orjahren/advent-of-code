#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int nWinningOptions(ll timeLimit, ll competitor)
{
    int res = 0;
    for (int i = 1; i < timeLimit; i++)
        if ((i * (timeLimit - i)) > competitor)
            res++;
    return res;
}
int main()
{
    bool isTest = false;
    int numsToRead = isTest ? 3 : 4;
    int x, part1 = 1;
    string inp;
    cin >> inp;
    vector<string> v(numsToRead);
    for (int i = 0; i < numsToRead; i++)
        cin >> v[i];
    string time = accumulate(v.begin(), v.end(), string(""));
    cin >> inp;
    for (int i = 0; i < numsToRead; i++)
    {
        cin >> inp;
        part1 *= nWinningOptions(stoll(v[i]), stoll(inp));
        v[i] = inp;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << nWinningOptions(stoll(time), stoll(accumulate(v.begin(), v.end(), string("")))) << endl;
}