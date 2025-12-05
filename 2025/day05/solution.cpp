#include <bits/stdc++.h>

using namespace std;

pair<int, int> parseLine(string &line)
{
    int splIdx = line.find("-");
    string a = line.substr(0, splIdx);
    string b = line.substr(splIdx + 1);
    pair<int, int> p = make_pair(stoi(a), stoi(b));
    cout << "Parret: " << endl;
    cout << p.first << endl;
    cout << p.second << endl;
    return p;
}

int main()
{
    string inp;
    int i = 0;
    vector<pair<int, int>> ranges;

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

    int minVal = -1;
    int maxVal = -1;
    for (int i = 0; i < ranges.size(); i++)
    {
        auto p = ranges[i];
        minVal = min(minVal, p.first);
        maxVal = max(maxVal, p.second);
    }
    cout << "Min og max: " << minVal << ", " << maxVal << endl;

    vector<int> queries;

    do
    {
        cout << "Inp 2: " << inp << ", iteratsjon: " << i++ << endl;
        int parsed = stoi(inp);
        cout << "Parsed query: " << parsed << endl;
        queries.push_back(parsed);
    } while (cin >> inp);
    cout << "Has " << queries.size() << " queries " << endl;

    int curr = 50;
    int p1 = 0;
    cout << "Part 1: " << p1 << endl;
}
