#include <bits/stdc++.h>

using namespace std;

#define REMOVED_FLAG -1
typedef long long ll;

int getValueP1(string &bank)
{
    int curr = 0;
    string cand;
    for (int i = 0; i < bank.size(); i++)
    {
        for (int j = i; j < bank.size(); j++)
        {
            if (i == j)
                continue;
            // string cand = bank[i] + bank[j];
            string cand = string(1, bank.at(i)) + bank[j];
            int val = stoi(cand);
            // cout << "val: " << val << endl;
            curr = max(curr, val);
        }
    }
    return curr;
}

map<char, int> getFreqMap(string &s)
{
    map<char, int> m;
    for (int i = 0; i < s.size(); i++)
    {
        m[s[i]]++;
    }
    return m;
}

vector<char> getUniqueCharsInString(string &s)
{
    vector<char> res;
    set<char> seen;
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        if (seen.find(c) == seen.end())
        {
            res.push_back(c);
            seen.insert(c);
        }
    }
    return res;
}

ll getValueP2(string bank) // <- merk pass by value
{
    int len = bank.size();
    cout << "Len: " << len << endl;

    int shouldPrune = len - 12;
    cout << "Should prune: " << shouldPrune << endl;

    auto freqMap = getFreqMap(bank);

    auto types = getUniqueCharsInString(bank);

    sort(types.begin(), types.end());

    for (int i = 0; i < types.size(); i++)
    {
        cout << types[i] << ": " << freqMap[types[i]] << endl;
    }

    for (int i = 0; i < shouldPrune; i++)
    {
        int removeIdx = 0;
        for (int j = 0; j < types.size(); j++)
        {
            if (freqMap[types[j]] > 0)
            {
                removeIdx = j;
                // TODO: Bruke vanlig break?
                goto fant;
            }
        }
    fant:
        char removeWhat = types[freqMap[removeIdx]];
        cout << "Skal fjerne en " << removeWhat << endl;

        // for (int j = len; j >= 0; j--)
        for (int j = 0; j < bank.size(); j++)
        {
            char cand = bank[j];
            if (cand != REMOVED_FLAG && cand == removeWhat)
            {
                bank[j] = REMOVED_FLAG;
                freqMap[cand]--;
                goto videre;
            }
        }
    videre:
    }

    string cand;

    for (int i = 0; i < bank.size(); i++)
    {
        if (bank[i] == REMOVED_FLAG)
            continue;

        cand += bank[i];
    }
    cout << "Final processed bank string: " << cand << endl;
    ll val = stoll(cand);
    cout << "Parse val: " << val << endl;
    return val; // curr = max(curr, val);
    // return curr;
}

int main()
{
    ll p1, p2;
    p1 = p2 = 0;
    string inp;
    int i = 0;
    while (cin >> inp)
    {
        cout << inp << endl;
        cout << "i: " << i++ << endl;
        p1 += getValueP1(inp);
        ll p2Val = getValueP2(inp);
        cout << "p2 val: " << p2Val << endl;
        p2 += p2Val;
    }
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}
