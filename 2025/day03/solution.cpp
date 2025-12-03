#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll getValue(string bank, int retainChars)
{
    int shouldPrune = bank.size() - retainChars;
    while (shouldPrune--)
    {
        int del;
        bool didDelete = false;
        for (int i = 1; i < bank.size(); i++)
        {
            if (bank[i] > bank[i - 1])
            {
                bank.erase(i - 1, 1);
                didDelete = true;
                break;
            }
            del = i;
        }
        if (!didDelete)
            bank.erase(del, 1);
    }
    return stoll(bank);
}

int main()
{
    ll p1, p2;
    p1 = p2 = 0;
    string inp;
    while (cin >> inp)
    {
        p1 += getValue(inp, 2);
        p2 += getValue(inp, 12);
    }
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}
