#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool optionWouldWin(ll opt, ll competitor, ll timeLimit)
{
    return (opt * (timeLimit - opt)) > competitor;
}

vector<ll> getWinningOptions(ll timeLimit, ll competitor)
{
    vector<ll> winningOptions;
    for (ll i = 0; i < timeLimit; i++)
    {
        if (optionWouldWin(i, competitor, timeLimit))
            winningOptions.push_back(i);
    }
    return winningOptions;
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
    string timesConcat = std::accumulate(times.begin(), times.end(), std::string(""));
    cin >> inp;
    for (int i = 0; i < numsToRead; i++)
    {
        cin >> inp;
        distances.push_back(inp);
    }
    string distanceConcat = accumulate(distances.begin(), distances.end(), std::string(""));

    cout << timesConcat << endl;
    cout << distanceConcat << endl;

    ll bigTime = stoll(timesConcat);
    ll bigDist = stoll(distanceConcat);

    ll res = getWinningOptions(bigTime, bigDist).size();

    cout << "Part 2: " << res << endl;
}