#include <bits/stdc++.h>
using namespace std;
bool charIsNum(char &c)
{
    return c >= '0' && c <= '9';
}

char stringToNum(string &s, vector<string> &nums)
{
    for (int i = 0; i < nums.size(); i++)
    {
        if (s == nums[i])
            return i + 1 + '0';
    }
    return -1;
}

int main()
{
    vector<string> nums = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string s, a, b;
    int partTwo = 0;
    while (cin >> s)
    {
        for (int i = 0; i < s.size(); i++)
        {
            if (charIsNum(s[i]))
            {
                a = s[i];
                goto sec;
            }
            for (auto &num : nums)
            {
                string candString = s.substr(i, num.size());
                if (candString == num)
                {
                    a = stringToNum(candString, nums);
                    goto sec;
                }
            }
        }
    sec:
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (charIsNum(s[i]))
            {
                b = s[i];
                goto ut;
            }
            for (auto &num : nums)
            {
                string candString = s.substr(i, num.size());
                if (candString == num)
                {
                    b = stringToNum(candString, nums);
                    goto ut;
                }
            }
        }
    ut:
        partTwo += stoi(a + b);
    }
    cout << "Part 2: " << partTwo << endl;
}