#include <bits/stdc++.h>
using namespace std;

struct numEnt
{
    string val;
    short idxStart;
    short idxEnd;
    int lineIdx;
};

bool numberIsAdjacentToSymbol(numEnt num, vector<string> lines)
{
    char symbols[] = {'*', '$', '#', '+', '-', '!', '%', '&', '/', '(', ')', '=', '@'};
    for (char symbol : symbols)
    {
        for (int idx = num.idxStart; idx <= num.idxEnd; idx++)
        {
            if (num.idxStart > 0 && lines[num.lineIdx][idx - 1] == symbol)
                return true;
            if (num.idxEnd < lines[num.lineIdx].size() - 1 && lines[num.lineIdx][idx + 1] == symbol)
                return true;

            if (num.lineIdx > 0)
            {
                if (num.idxStart > 0 && lines[num.lineIdx - 1][idx - 1] == symbol)
                    return true;
                if (num.idxEnd < lines[num.lineIdx - 1].size() - 1 && lines[num.lineIdx - 1][idx + 1] == symbol)
                    return true;
            }

            if (num.lineIdx < lines.size() - 1)
            {
                if (num.idxStart > 0 && lines[num.lineIdx + 1][idx - 1] == symbol)
                    return true;
                if (num.idxEnd < lines[num.lineIdx + 1].size() - 1 && lines[num.lineIdx + 1][idx + 1] == symbol)
                    return true;
            }
            if (num.lineIdx > 0 && lines[num.lineIdx - 1][idx] == symbol)
                return true;
            if (num.lineIdx < lines.size() - 1 && lines[num.lineIdx + 1][idx] == symbol)
                return true;
        }
    }
    return false;
}

bool charIsNumeric(char c)
{
    return (c >= '0' && c <= '9');
}

int main()
{
    string s;
    vector<numEnt> nums;
    vector<string> lines;
    while (cin >> s)
    {
        lines.push_back(s);
        for (int i = 0; i < s.size(); i++)
        {
            if (charIsNumeric(s[i]))
            {
                numEnt num;
                num.idxStart = i;
                num.lineIdx = lines.size() - 1;
                int j = i;
                while (j < s.size() && charIsNumeric(s[j]))
                    j++;
                num.idxEnd = j - 1;
                string numStr = s.substr(num.idxStart, num.idxEnd - num.idxStart + 1);
                num.val = numStr;
                nums.push_back(num);
                i = j;
            }
        }
    }
    int res = 0;
    for (numEnt num : nums)
        res += numberIsAdjacentToSymbol(num, lines) ? stoi(num.val) : 0;
    cout << "Part 1: " << res << endl;
}