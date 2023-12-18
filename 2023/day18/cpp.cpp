#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
pair<ll, ll> getDirPairFromChar(char c)
{
    pair<ll, ll> arr[] = {make_pair(0, 1), make_pair(1, 0), make_pair(0, -1), make_pair(-1, 0)};
    char chars[] = {'R', 'D', 'L', 'U'};
    for (int i = 0; i < 4; i++)
    {
        if (c == chars[i] || c == i + '0')
        {
            return arr[i];
        }
    }
    cout << "Error: " << c << endl;
    exit(1);
}
pair<ll, ll> getDirFromHex(string arg)
{
    char c = arg[arg.size() - 2];
    return getDirPairFromChar(c);
}
ll convHexToDec(string arg)
{
    string hexVal = arg.substr(2, arg.size() - 4);
    stringstream stream;
    stream << hexVal;
    ll y;
    stream >> hex >> y;
    return y;
}
ll solveFromListOfPairs(vector<pair<ll, ll>> &borderPoints, ll b)
{
    ll outerArea = 0;
    for (int i = 0; i < borderPoints.size(); i++)
    {
        pair<ll, ll> &px = i == 0 ? borderPoints.back() : borderPoints[i - 1];
        pair<ll, ll> &py = borderPoints[(i + 1) % (borderPoints.size())];
        outerArea += borderPoints[i].first * (px.second - py.second);
    }
    outerArea = abs(outerArea) / 2;
    ll innerArea = ceil((outerArea - (b / 2)) + 1);
    return innerArea + b;
}
int main()
{
    char dir;
    ll val;
    string hash;
    vector<pair<ll, ll>> part1Points;
    vector<pair<ll, ll>> part2Points;
    part1Points.push_back(make_pair(0, 0));
    part2Points.push_back(make_pair(0, 0));
    ll b1 = 0, b2 = 0;
    while (cin >> dir >> val >> hash)
    {
        pair<ll, ll> part1Pair = getDirPairFromChar(dir);
        pair<ll, ll> part2Pair = getDirFromHex(hash);

        pair<ll, ll> &last1 = part1Points.back();
        pair<ll, ll> &last2 = part2Points.back();

        b1 += val;

        ll num = convHexToDec(hash);
        b2 += num;

        part1Points.push_back(make_pair(last1.first + part1Pair.first * val, last1.second + part1Pair.second * val));
        part2Points.push_back(make_pair(last2.first + part2Pair.first * num, last2.second + part2Pair.second * num));
    }
    ll part1 = solveFromListOfPairs(part1Points, b1);
    ll part2 = solveFromListOfPairs(part2Points, b2);
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}