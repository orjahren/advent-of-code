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
    vector<string> times;
    vector<string> distances;
    string inp;
    cin >> inp;

    bool isTest = false;
    int numsToRead = isTest ? 3 : 4;

    for (int i = 0; i < numsToRead; i++)
    {
        cin >> inp;
        times.push_back(inp);
    }
    string timesConcat = accumulate(times.begin(), times.end(), string(""));
    cin >> inp;
    for (int i = 0; i < numsToRead; i++)
    {
        cin >> inp;
        distances.push_back(inp);
    }
    string distanceConcat = accumulate(distances.begin(), distances.end(), string(""));

    cout << timesConcat << endl;
    cout << distanceConcat << endl;

    ll bigTime = stoll(timesConcat);
    ll bigDist = stoll(distanceConcat);

    cout << "Part 2: " << howManyWinningOptions(bigTime, bigDist) << endl;
}