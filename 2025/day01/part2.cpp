#include <bits/stdc++.h>

using namespace std;

int getIntFromStr(string &s)
{
    return stoi(s.substr(1));
}
int main()
{
    int curr = 50;
    int p2 = 0;
    string inp;
    while (cin >> inp)
    {
        cout << inp << endl;
        int dist = getIntFromStr(inp);
        cout << dist << endl;
        for (int i = 0; i < dist; i++)
        {
            if (curr == 0)
                p2++;

            if (inp[0] == 'L')
            {
                curr--;
            }
            else
            {
                curr++;
            }
            curr %= 100;
        }
    }
    cout << "Part 2: " << p2 << endl;

    return 0;
}
