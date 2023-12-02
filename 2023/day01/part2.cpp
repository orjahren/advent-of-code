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

void maybeSet(string &s, vector<string> &nums, int &idx, string &target)
{
    for (auto &num : nums)
    {
        string candString = s.substr(idx, num.size());
        if (candString == num)
        {
            target = stringToNum(candString, nums);
        }
    }
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
                b = s[i];
            maybeSet(s, nums, i, b);
            int j = s.size() - i - 1;
            if (charIsNum(s[j]))
                a = s[j];
            maybeSet(s, nums, j, a);
        }
        partTwo += stoi(a + b);
    }
    cout << "Part 2: " << partTwo << endl;
}