#include <bits/stdc++.h>

using namespace std;

int main()
{
    int curr = 50;
    int p2 = 0;
    string inp;
    while (cin >> inp)
    {
        for (int i = 0; i < stoi(inp.substr(1)); i++)
        {
            if (curr == 0)
                p2++;
            if (inp[0] == 'L')
                curr--;
            else
                curr++;
            curr %= 100;
        }
    }
    cout << "Part 2: " << p2 << endl;
}
