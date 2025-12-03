#include <bits/stdc++.h>

using namespace std;

#define REMOVED_FLAG 'x'
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

    // auto freqMap = getFreqMap(bank);

    // auto types = getUniqueCharsInString(bank);

    // sort(types.begin(), types.end());

    // for (int i = 0; i < types.size(); i++)
    //{
    // cout << types[i] << ": " << freqMap[types[i]] << endl;
    //}

    while (shouldPrune--)
    {
        int removeIdx = 0;
        // char removeWhat = types[freqMap[removeIdx]];
        // char removeWhat = types[removeIdx];
        // cout << "Skal fjerne en " << removeWhat << endl;

        // for (int j = len; j >= 0; j--)
        int del;
        for (int i = 1; i < bank.size(); i++)
        {
            cout << "I er " << i << endl;
            char cand = bank[i];
            cout << "cand er " << cand << endl;
            int prevIdx = i - 1;
            cout << "Første prev idx er " << prevIdx << endl;
            while (bank[prevIdx] == REMOVED_FLAG)
            {

                // cout << "Dekrementrer prev idx " << endl;
                prevIdx--;
                if (prevIdx < 0)
                {
                    // Kommer vi under 0 uten å finne noe må vi lete andre veien :D This is fine
                    prevIdx = 0;
                    goto hack;
                }
            }
            goto hopp;
        hack:
            while (bank[prevIdx] == REMOVED_FLAG || prevIdx == i)
            {

                // cout << "INKREMENTERER prev idx " << endl;
                prevIdx++;
            }
        hopp:
            cout << "Beregnet prev idx: " << prevIdx << endl;
            if (cand == REMOVED_FLAG || bank[prevIdx] == REMOVED_FLAG)
                continue;
            if (cand > bank[prevIdx])
            {
                cout << "Loop-fjerner " << bank[prevIdx] << " på idx " << prevIdx << endl;
                cout << "Nå skjer det" << endl;
                bank[prevIdx] = REMOVED_FLAG;
                cout << "Nå er det gjort :)" << endl;

                // freqMap[cand]--;
                goto videre;
            }
            del = i;
        }
        // ^hvis ikke noe ble fjernet over, må vi fjerne oss selv
        cout << "Edge fjerner " << bank[del] << " på idx " << del << endl;
        bank[del] = REMOVED_FLAG;
    videre:
    }

    string cand;

    for (int i = 0; i < bank.size(); i++)
    {
        if (bank[i] == REMOVED_FLAG)
            continue;

        cand += bank[i];
    }
    cout << "Final processed cand string: " << cand << endl;
    cout << "Mutated bank string: " << bank << endl;
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
