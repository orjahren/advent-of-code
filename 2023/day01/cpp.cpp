#include <bits/stdc++.h>
using namespace std;
bool charIsNum(char &c)
{
    return c >= '0' && c <= '9';
}

int main()
{
    vector<string> nums = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string s;
    int partOne, x, y;
    char a, b;
    partOne = 0;
    while (cin >> s)
    {
        cout << s << endl;
        for (int i = 0; i < s.size(); i++)
        {
            cout << s[i] << endl;
            if (charIsNum(s[i]))
            {
                a = s[i];
                break;
            }
        }
        cout << "ANDRE" << endl;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            cout << s[i] << endl;
            if (charIsNum(s[i]))
            {
                b = s[i];
                break;
            }
        }
        cout << "Første: " << a << endl;
        cout << "Sidste: " << b << endl;

        string comp{a, b};
        cout << comp << endl;
        int parsed = stoi(comp);
        cout << parsed << endl;
        partOne += parsed;
    }
    cout << "Part 1: " << partOne << endl;
}