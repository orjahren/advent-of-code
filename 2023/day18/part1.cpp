#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll convHexToDec(string arg)
{
    string hexVal = arg.substr(2, arg.size() - 4);
    cout << "hexVal = " << hexVal << endl;
    stringstream stream;
    stream << hexVal;
    ll y;
    stream >> hex >> y;
    return y;
}

pair<int, int> getDirPairFromChar(char c)
{
    pair<int, int> arr[] = {make_pair(0, 1), make_pair(1, 0), make_pair(0, -1), make_pair(-1, 0)};
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

int main()
{
    char dir;
    int val;
    string hash;
    vector<pair<int, int>> borderPoints;
    borderPoints.push_back(make_pair(0, 0));
    ll b = 0;
    while (cin >> dir >> val >> hash)
    {
        pair<int, int> dirPair = getDirPairFromChar(dir);
        b += val;
        pair<int, int> &last = borderPoints.back();
        borderPoints.push_back(make_pair(last.first + dirPair.first * val, last.second + dirPair.second * val));
    }
    ll outerArea = 0;
    for (int i = 0; i < borderPoints.size(); i++)
    {
        pair<int, int> &px = i == 0 ? borderPoints.back() : borderPoints[i - 1];
        pair<int, int> &py = borderPoints[(i + 1) % (borderPoints.size())];
        outerArea += borderPoints[i].first * (px.second - py.second);
    }
    outerArea = abs(outerArea) / 2;
    ll innerArea = ceil((outerArea - (b / 2)) + 1);
    ll part1 = innerArea + b;
    cout << "Part 1: " << part1 << endl;
}