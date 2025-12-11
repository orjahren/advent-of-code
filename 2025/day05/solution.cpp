#include <iostream>

typedef long long ll;

using namespace std;

pair<ll, ll> parseLine(string &line)
{
    int splIdx = line.find("-");
    string a = line.substr(0, splIdx);
    string b = line.substr(splIdx + 1);
    pair<ll, ll> p = make_pair(stoll(a), stoll(b));
    cout << "Parret: " << endl;
    cout << p.first << endl;
    cout << p.second << endl;
    return p;
}
bool myComparison(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
    if (a.first != b.first)
        return a.first < b.first;
    return a.second < b.second;
}

bool isFresh(ll val, vector<pair<ll, ll>> &ranges)
{

    cout << "\tSjekker freshness for " << val << endl;
    auto startPoint = lower_bound(ranges.begin(), ranges.end(), make_pair(val, numeric_limits<ll>::min()));
    int startIdx = (startPoint - ranges.begin()) - 1;
    cout << "Startidx: " << startIdx << endl;
    for (int i = startIdx; i < ranges.size(); i++)
    {
        pair<ll, ll> &p = ranges[i];

        cout << "Pair " << p.first << ", " << p.second << endl;
        // bool localGood = p.first <= val && p.second >= val;
        bool localGood = p.first <= val && p.second >= val;
        if (localGood)
        {
            cout << "OK" << endl;
            return true;
        }
        else
        {
            cout << "MØTER IKKE DETTE KRAVET" << endl;
        }
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
    int i = 0;
    vector<pair<ll, ll>> ranges;

    while (cin >> inp)
    {
        cout << "Inp 1: " << inp << ", iteratsjon: " << i++ << endl;
        // cout << inp.find("-") << endl;
        if (inp.find("-") == string::npos)
        {
            break;
        }
        auto p = parseLine(inp);
        ranges.push_back(p);
    }

    // Sorterer parene på FIRST slik at vi kan gjøre binærsøk for å filtrere ut de som er relevante å sjekke
    cout << "Sorting pairs...";
    sort(ranges.begin(), ranges.end(), myComparison);
    cout << "..done" << endl;

    vector<ll> queries;

    do
    {
        cout << "Inp 2: " << inp << ", iteratsjon: " << i++ << endl;
        ll parsed = stoll(inp);
        cout << "Parsed query: " << parsed << endl;
        queries.push_back(parsed);
    } while (cin >> inp);
    cout << "Has " << queries.size() << " queries " << endl;

    int p1 = 0;

    for (int i = 0; i < queries.size(); i++)
    {
        ll query = queries[i];
        if (isFresh(query, ranges))
        {
            p1++;
            cout << " ID " << query << " ER fresh " << endl;
        }
    }

    cout << "Part 1: " << p1 << endl;

    ll p2 = getP2(ranges);
    cout << "Part 2: " << p2 << endl;
}
