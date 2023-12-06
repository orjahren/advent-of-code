#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool optionWouldWin(ll opt, ll competitor, ll timeLimit)
{
    return (opt * (timeLimit - opt)) > competitor;
}

int howManyWinningOptions(ll timeLimit, ll competitor)
{
    int res = 0;
    for (ll i = 0; i < timeLimit; i++)
    {
        if (optionWouldWin(i, competitor, timeLimit))
            res++;
    }
    return res;
}

int main()
{
    vector<string> v;
    string inp;
    cin >> inp;

    bool isTest = false;
    int numsToRead = isTest ? 3 : 4;

    for (int i = 0; i < numsToRead; i++)
    {
        cin >> inp;
        v.push_back(inp);
    }
    cin >> inp;
    string time = accumulate(v.begin(), v.end(), string(""));
    v.clear();
    for (int i = 0; i < numsToRead; i++)
    {
        cin >> inp;
        v.push_back(inp);
    }
    string dist = accumulate(v.begin(), v.end(), string(""));
    cout << "Part 2: " << howManyWinningOptions(stoll(time), stoll(dist)) << endl;
}