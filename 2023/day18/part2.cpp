#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
pair<ll, ll> getDirPairFromChar(char c);
pair<ll, ll> getDirFromHex(string arg)
{
    char c = arg[arg.size() - 2];
    return getDirPairFromChar(c);
}
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

int main()
{
    char dir;
    ll val;
    string hash;
    vector<pair<ll, ll>> borderPoints;
    borderPoints.push_back(make_pair(0, 0));
    ll b = 0;
    while (cin >> dir >> val >> hash)
    {
        cout << hash << endl;
        pair<ll, ll> dirPair = getDirFromHex(hash);
        ll num = convHexToDec(hash);
        cout << "num = " << num << endl;
        b += num;
        pair<ll, ll> &last = borderPoints.back();
        borderPoints.push_back(make_pair(last.first + dirPair.first * num, last.second + dirPair.second * num));
    }
    ll outerArea = 0;
    for (int i = 0; i < borderPoints.size(); i++)
    {
        pair<ll, ll> &px = i == 0 ? borderPoints.back() : borderPoints[i - 1];
        pair<ll, ll> &py = borderPoints[(i + 1) % (borderPoints.size())];
        outerArea += borderPoints[i].first * (px.second - py.second);
    }
    outerArea = abs(outerArea) / 2;
    ll innerArea = ceil((outerArea - (b / 2)) + 1);
    ll part2 = innerArea + b;
    cout << "Part 2: " << part2 << endl;
}