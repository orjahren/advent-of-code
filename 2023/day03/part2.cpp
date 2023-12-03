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
struct gearEnt
{
    short pos;
    int lineIdx;
};

bool charIsNumeric(char c)
{
    return (c >= '0' && c <= '9');
}

bool gearIsAdjacentToNumber(gearEnt gent, numEnt num)
{
    bool isValid = false;
    for (int idx = num.idxStart; idx <= num.idxEnd; idx++)
    {
        if (num.lineIdx == gent.lineIdx || num.lineIdx - 1 == gent.lineIdx || num.lineIdx + 1 == gent.lineIdx)
        {
            isValid |= idx == gent.pos || idx + 1 == gent.pos || idx - 1 == gent.pos;
        }
    }
    return isValid;
}
int getValIdValidGear(gearEnt gear, vector<numEnt> nums)
{
    int adjecentNums = 0;
    int a, b;
    for (numEnt num : nums)
    {
        if (gearIsAdjacentToNumber(gear, num))
        {
            adjecentNums++;
            if (adjecentNums == 1)
                a = num.numVal;
            else
                b = num.numVal;
        }
    }
    return adjecentNums == 2 ? a * b : 0;
}

int main()
{
    string s;
    vector<numEnt> nums;
    int lineCounter = 0;
    vector<string> lines;
    while (cin >> s && ++lineCounter)
    {
        lines.push_back(s);
        for (int i = 0; i < s.size(); i++)
        {
            if (charIsNumeric(s[i]))
            {
                numEnt num;
                num.idxStart = i;
                num.lineIdx = lineCounter - 1;
                int j = i;
                while (j < s.size() && charIsNumeric(s[j]))
                    j++;
                num.idxEnd = j - 1;
                string numStr = s.substr(num.idxStart, num.idxEnd - num.idxStart + 1);
                int parsed = stoi(numStr);
                num.stringVal = numStr;
                num.numVal = parsed;
                nums.push_back(num);

                i = j;
            }
        }
    }

    vector<gearEnt> possibleGears;
    for (int lineCounter = 0; lineCounter < lines.size(); lineCounter++)
    {
        string line = lines[lineCounter];
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '*')
            {
                gearEnt gear;
                gear.pos = i;
                gear.lineIdx = lineCounter;
                possibleGears.push_back(gear);
            }
        }
    }
    int res = 0;
    for (gearEnt gear : possibleGears)
        res += getValIdValidGear(gear, nums);
    cout << "Part 2: " << res << endl;
}