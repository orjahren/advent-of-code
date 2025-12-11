#include <iostream>

typedef long long ll;

using namespace std;

pair<ll, ll> parseLine(string &line)
{
    int splIdx = line.find("-");
    string a = line.substr(0, splIdx);
    string b = line.substr(splIdx + 1);
    pair<ll, ll> p = make_pair(stoll(a), stoll(b));
    return p;
}

// TODO: Burde kunne merge disse...
bool p1Sort(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
    return a.second < b.second;
}
bool p2Sort(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
    if (a.first != b.first)
        return a.first < b.first;
    return a.second < b.second;
}

bool isFresh(ll val, vector<pair<ll, ll>> &ranges)
{
    auto startPoint = lower_bound(ranges.begin(), ranges.end(), make_pair(val, numeric_limits<ll>::min()));
    int startIdx = (startPoint - ranges.begin()) - 1;
    for (int i = startIdx; i < ranges.size(); i++)
    {
        auto [lo, hi] = ranges[i];
        if (lo <= val && hi >= val)
            return true;
    }
    return false;
}

ll getP2(vector<pair<ll, ll>> &ranges)
{

    ll res = 0;
    ll currStart = ranges[0].first;
    ll currEnd = ranges[0].second;

    for (int i = 1; i < ranges.size(); ++i)
    {
        const auto &seg = ranges[i];
        if (seg.first <= currEnd)
        {
            currEnd = max(currEnd, seg.second);
        }
        else
        {
            res += (currEnd - currStart + 1);
            currStart = seg.first;
            currEnd = seg.second;
        }
    }

    res += (currEnd - currStart + 1);
    return res;
}

int main()
{
    string inp;
    vector<pair<ll, ll>> ranges;

    while (cin >> inp)
    {
        if (inp.find("-") == string::npos)
        {
            break;
        }
        auto p = parseLine(inp);
        ranges.push_back(p);
    }

    ll p1 = 0;
    sort(ranges.begin(), ranges.end(), p1Sort);
    do
    {
        ll query = stoll(inp);
        if (isFresh(query, ranges))
            p1++;
    } while (cin >> inp);
    cout << "Part 1: " << p1 << endl;

    sort(ranges.begin(), ranges.end(), p2Sort);
    ll p2 = getP2(ranges);
    cout << "Part 2: " << p2 << endl;
}
