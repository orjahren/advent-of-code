#include <bits/stdc++.h>
using namespace std;
int nWinningOptions(int timeLimit, int competitor)
{
    int res = 0;
    for (int i = 1; i < timeLimit; i++)
        if ((i * (timeLimit - i)) > competitor)
            res++;
    return res;
}
int main()
{
    string devNull;
    cin >> devNull;
    int x, res = 1;
    bool isTest = false;
    int numsToRead = isTest ? 3 : 4;
    vector<int> times(numsToRead);
    for (int i = 0; i < numsToRead; i++)
        cin >> times[i];
    cin >> devNull;
    for (int i = 0; i < numsToRead; i++)
    {
        cin >> x;
        res *= nWinningOptions(times[i], x);
    }
    cout << "Part 1: " << res << endl;
}