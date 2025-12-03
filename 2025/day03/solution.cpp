#include <bits/stdc++.h>

using namespace std;

int getValue(string &bank)
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

int main()
{
    int p1 = 0;
    string inp;
    int i = 0;
    while (cin >> inp)
    {
        cout << inp << endl;
        cout << "i: " << i++ << endl;
        int val = getValue(inp);
        cout << "Value: " << val << endl;
        p1 += val;
    }
    cout << "Part 1: " << p1 << endl;
}
