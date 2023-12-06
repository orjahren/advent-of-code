#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int howManyWinningOptions(ll timeLimit, ll competitor)
{
    int res = 0;
    for (ll i = 0; i < timeLimit; i++)
        if ((i * (timeLimit - i)) > competitor)
            res++;
    return res;
}
int main()
{
    bool isTest = false;
    int numsToRead = isTest ? 3 : 4;
    string inp;
    cin >> inp;
    vector<string> v(numsToRead);
    for (int i = 0; i < numsToRead; i++)
        cin >> v[i];
    cin >> inp;
    string time = accumulate(v.begin(), v.end(), string(""));
    for (int i = 0; i < numsToRead; i++)
        cin >> v[i];
    cout << "Part 2: " << howManyWinningOptions(stoll(time), stoll(accumulate(v.begin(), v.end(), string("")))) << endl;
}