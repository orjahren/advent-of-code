#include <bits/stdc++.h>
using namespace std;

struct numEnt
{
    int numVal;
    string stringVal;
    short idxStart;
    short idxEnd;
    int lineIdx;
};

bool numberIsAdjacentToSymbol(numEnt num, vector<string> lines)
{
    char symbols[] = {'*', '$', '#', '+'};
    for (char symbol : symbols)
    {
        for (int idx = num.idxStart; idx <= num.idxEnd; idx++)
        {
            // To the left of curr num
            if (num.idxStart > 0 && lines[num.lineIdx][idx - 1] == symbol)
            {
                return true;
            }
            // To the right on same line
            if (num.idxEnd < lines[num.lineIdx].size() - 1 && lines[num.lineIdx][idx + 1] == symbol)
            {
                return true;
            }

            // check diagonally
            if (num.lineIdx > 0)
            {
                // top left
                if (num.idxStart > 0 && lines[num.lineIdx - 1][idx - 1] == symbol)
                {
                    return true;
                }
                // top right
                if (num.idxEnd < lines[num.lineIdx - 1].size() - 1 && lines[num.lineIdx - 1][idx + 1] == symbol)
                {
                    return true;
                }
            }

            if (num.lineIdx < lines.size() - 1)
            {
                // bottom left
                if (num.idxStart > 0 && lines[num.lineIdx + 1][idx - 1] == symbol)
                {
                    return true;
                }
                // bottom right
                if (num.idxEnd < lines[num.lineIdx + 1].size() - 1 && lines[num.lineIdx + 1][idx + 1] == symbol)
                {
                    return true;
                }
            }
            // check above and under
            // above
            if (num.lineIdx > 0 && lines[num.lineIdx - 1][idx] == symbol)
            {
                return true;
            }
            // under
            if (num.lineIdx < lines.size() - 1 && lines[num.lineIdx + 1][idx] == symbol)
            {
                return true;
            }
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
    int lineCounter = 0;
    vector<string> lines;
    while (cin >> s && ++lineCounter)
    {
        cout << s << endl;
        lines.push_back(s);
        for (int i = 0; i < s.size(); i++)
        {
            if (charIsNumeric(s[i]))
            {
                numEnt num;
                num.idxStart = i;
                num.lineIdx = lineCounter - 1;
                cout << s[i] << " Es un numero" << endl;
                int j = i;
                while (j < s.size() && charIsNumeric(s[j]))
                {
                    j++;
                }
                num.idxEnd = j - 1;
                cout << "Found num from " << num.idxStart << " to " << num.idxEnd << endl;
                string numStr = s.substr(num.idxStart, num.idxEnd - num.idxStart + 1);
                cout << "NumStr: " << numStr << endl;
                int parsed = stoi(numStr);
                cout << "Parsed: " << parsed << endl;
                num.stringVal = numStr;
                num.numVal = parsed;
                nums.push_back(num);

                i = j;
            }
        }
    }
    cout << "Found " << nums.size() << " numbers" << endl;
    int res = 0;
    for (numEnt num : nums)
    {
        if (numberIsAdjacentToSymbol(num, lines))
        {
            cout << "Found valid num " << num.numVal << " at line " << num.lineIdx << endl;
            res += num.numVal;
        }
        else
        {
            cout << "\t Not valid num " << num.numVal << " at line " << num.lineIdx << endl;
        }
    }
    cout << "Part 1: " << res << endl;
}