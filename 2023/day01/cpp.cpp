#include <bits/stdc++.h>
using namespace std;
bool charIsNum(char &c)
{
    return c >= '0' && c <= '9';
}

int stringToNum(string &s, vector<string> &nums)
{
    for (int i = 0; i < nums.size(); i++)
    {
        if (s == nums[i])
            return i + 1;
    }
    return -1;
}

bool stringIsNumber(string &s, vector<string> &nums)
{
    if (s.size() == 0)
        return charIsNum(s[0]);
    return stringToNum(s, nums) != -1;
}

int main()
{
    vector<string> nums = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string s;
    int partOne, partTwo, x, y;
    char a, b;
    partOne = partTwo = 0;
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