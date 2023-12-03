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

bool gearIsAdjacentToNumber(gearEnt gent, numEnt num);
int getValIdValidGear(gearEnt gear, vector<numEnt> nums)
{
    // check if gear is adjecent to exactly 2 numbers {
    int adjecentNums = 0;
    int a, b;
    for (numEnt num : nums)
    {
        if (gearIsAdjacentToNumber(gear, num))
        {
            cout << "Gear at line " << gear.lineIdx << ", idx " << gear.pos << " is adjecent to " << num.stringVal << endl;
            adjecentNums++;
            if (adjecentNums == 1)
            {
                a = num.numVal;
            }
            else
            {
                b = num.numVal;
            }
        }
    }
    if (adjecentNums == 2)
    {
        cout << "Found valid gear at " << gear.lineIdx << ", " << gear.pos << endl;
        return a * b;
    }
    else
    {
        cout << "invalid gear at " << gear.lineIdx << ", " << gear.pos << endl;
        cout << "adjecentNums: " << adjecentNums << endl;
        return 0;
    }
}

bool gearIsAdjacentToNumber(gearEnt gent, numEnt num)
{
    for (int idx = num.idxStart; idx <= num.idxEnd; idx++)
    {
        // To the left of curr num
        if (num.lineIdx == gent.lineIdx && idx - 1 == gent.pos)
        {
            return true;
        }
        // To the right on same line
        if (num.lineIdx == gent.lineIdx && idx + 1 == gent.pos)
        {
            return true;
        }

        // check diagonally
        if (num.lineIdx > 0)
        {
            // top left
            if (num.lineIdx - 1 == gent.lineIdx && idx - 1 == gent.pos)
            {
                return true;
            }
            // top right
            if (num.lineIdx - 1 == gent.lineIdx && idx + 1 == gent.pos)
            {
                return true;
            }
        }

        // bottom left
        if (num.lineIdx + 1 == gent.lineIdx && idx - 1 == gent.pos)
        {
            return true;
        }
        // bottom right
        if (num.lineIdx + 1 == gent.lineIdx && idx + 1 == gent.pos)
        {
            return true;
        }
        // check above and under
        // above
        if (num.lineIdx - 1 == gent.lineIdx && idx == gent.pos)
        {
            return true;
        }
        // under
        if (num.lineIdx + 1 == gent.lineIdx && idx == gent.pos)
        {
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

    // find all gears
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
    cout << "Found " << possibleGears.size() << " possible gears" << endl;
    int res = 0;
    for (gearEnt gear : possibleGears)
    {
        res += getValIdValidGear(gear, nums);
    }
    cout << "Part 2: " << res << endl;
}