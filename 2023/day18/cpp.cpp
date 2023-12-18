#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> p;
p getDirPairFromChar(char c)
{
    p arr[] = {make_pair(0, 1), make_pair(1, 0), make_pair(0, -1), make_pair(-1, 0)};
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
p getDirFromHex(string arg)
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
ll solveFromListOfPairs(vector<p> &borderPoints, ll b)
{
    ll outerArea = 0;
    for (int i = 0; i < borderPoints.size(); i++)
    {
        p &px = i == 0 ? borderPoints.back() : borderPoints[i - 1];
        p &py = borderPoints[(i + 1) % (borderPoints.size())];
        outerArea += borderPoints[i].first * (px.second - py.second);
    }
    outerArea = abs(outerArea) / 2;
    ll innerArea = ceil((outerArea - (b / 2)) + 1);
    return innerArea + b;
}
int main()
{
    vector<p> part1Points;
    vector<p> part2Points;
    part1Points.push_back(make_pair(0, 0));
    part2Points.push_back(make_pair(0, 0));
    ll val, b1 = 0, b2 = 0;
    char dir;
    string hash;
    while (cin >> dir >> val >> hash)
    {
        p part1Pair = getDirPairFromChar(dir);
        p part2Pair = getDirFromHex(hash);

        p &last1 = part1Points.back();
        p &last2 = part2Points.back();

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