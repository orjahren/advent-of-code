#include <bits/stdc++.h>

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

    ll minVal = ranges[0].first;
    ll maxVal = ranges[0].second;
    for (int i = 0; i < ranges.size(); i++)
    {
        auto p = ranges[i];
        minVal = min(minVal, p.first);
        maxVal = max(maxVal, p.second);
    }
    cout << "Min og max: " << minVal << ", " << maxVal << endl;
    ll spenn = maxVal - minVal;
    cout << "Spenn: " << spenn << endl;
    char flags[spenn];
    memset(flags, 0, sizeof(char) * spenn);

    for (int i = 0; i < ranges.size(); i++)
    {
        auto p = ranges[i];
        cout << "Behandler par " << p.first << ", " << p.second << endl;
        // TODO: Burde optimalisere dette
        for (ll j = p.first; j <= p.second; j++)
        {
            ll idx = j - minVal;
            cout << "Tagger " << idx << endl;
            flags[j - minVal] = 1;
        }
    }

    vector<int> queries;

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
        int query = queries[i];
        cout << "Sjekker ID " << query << endl;
        if (query < minVal || query > maxVal)
        {

            cout << "Auto-continuer" << endl;
            continue;
        }
        cout << "Verdien er " << (int)(flags[query - minVal]) << " og idx er " << query - minVal << endl;
        if (flags[query - minVal])
        {
            p1++;
            cout << "ER fresh " << endl;
        }
    }

    cout << "Part 1: " << p1 << endl;
}
