#include <bits/stdc++.h>
using namespace std;
bool optionWouldWin(int opt, int competitor, int timeLimit)
{
    int currentSpeedInMs = 0;
    int speedIncreasesByMsPrSec = 1;
    // TODO: There must be some way to do this in O(1) time lol
    // Set currSped = opt and no loop?
    for (int i = 0; i < opt; i++)
    {
        currentSpeedInMs += speedIncreasesByMsPrSec;
    }
    return (currentSpeedInMs * (timeLimit - opt)) > competitor;
}

vector<int> getWinningOptions(int timeLimit, int competitor)
{
    vector<int> winningOptions;
    for (int i = 0; i < timeLimit; i++)
    {
        if (optionWouldWin(i, competitor, timeLimit))
            winningOptions.push_back(i);
    }
    return winningOptions;
}

int main()
{
    vector<int> times;
    vector<int> distances;
    string devNull;
    cin >> devNull;
    int x;

    bool isTest = false;
    int numsToRead = isTest ? 3 : 4;

    for (int i = 0; i < numsToRead; i++)
    {
        cin >> x;
        times.push_back(x);
    }
    cin >> devNull;
    for (int i = 0; i < numsToRead; i++)
    {
        cin >> x;
        distances.push_back(x);
    }

    int res = 1;
    for (int i = 0; i < numsToRead; i++)
        res *= getWinningOptions(times[i], distances[i]).size();

    cout << "Part 1: " << res << endl;
}