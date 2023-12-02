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
    int partTwo, x, y;
    string a, b;
    partTwo = 0;
    while (cin >> s)
    {
        cout << "***************" << endl;
        cout << s << endl;
        for (int i = 0; i < s.size(); i++)
        {
            cout << s[i] << endl;
            if (charIsNum(s[i]))
            {
                a = s[i];
                break;
            }
            for (auto &num : nums)
            {
                // cout << "Skal lage candstring" << endl;
                //  string candString = s.substr(i - num.size() + 1, num.size());
                string candString = s.substr(i, num.size());

                cout << "laget candstring: " << candString << endl;
                if (candString == num)
                {
                    a = candString;
                    a = to_string(stringToNum(a, nums));
                    cout << "FANT NUMMER: " << a << endl;
                    goto andre;
                    break;
                }
            }
        }
    andre:
        cout << "ANDRE" << endl;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            cout << s[i] << endl;
            if (charIsNum(s[i]))
            {
                b = s[i];
                break;
            }
            for (auto &num : nums)
            {
                string candString = s.substr(i, num.size());
                if (candString == num)
                {
                    b = candString;
                    b = to_string(stringToNum(b, nums));
                    cout << "FANT NUMMER: " << b << endl;
                    goto ut;
                    break;
                }
            }
        }
    ut:
        cout << "Første: " << a << endl;
        cout << "Sidste: " << b << endl;

        string comp = a + b;
        cout << comp << endl;
        int parsed = stoi(comp);
        cout << parsed << endl;
        partTwo += parsed;
    }
    cout << "Part 2: " << partTwo << endl;
}