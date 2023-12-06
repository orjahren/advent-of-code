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
    cout << "Hello World!" << endl;
    vector<int> times(3);
    vector<int> distances(3);
    string devNull;
    cin >> devNull;
    for (int i = 0; i < 3; i++)
        cin >> times[i];
    cin >> devNull;
    for (int i = 0; i < 3; i++)
        cin >> distances[i];
    cout << "Times: ";
    for (int i = 0; i < 3; i++)
        cout << times[i] << " ";
    cout << endl;
    cout << "Distances: ";
    for (int i = 0; i < 3; i++)
        cout << distances[i] << " ";
    cout << endl;

    // int vals[3][3];
    vector<vector<int>> vals(3, vector<int>(3));
    int res = 1;
    for (int i = 0; i < 3; i++)
    {
        cout << "i: " << i << ", would win with " << endl;
        vector<int> winningOptions = getWinningOptions(times[i], distances[i]);
        vals[i] = winningOptions;

        for (int j = 0; j < winningOptions.size(); j++)
            cout << winningOptions[j] << " ";
        cout << endl
             << "i.e. " << vals[i].size() << " options" << endl;
        res *= vals[i].size();
    }
    cout << "Part 1: " << res << endl;
}