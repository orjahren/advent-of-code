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
    free(flags);

    cout << "Part 1: " << p1 << endl;
}
