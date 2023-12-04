#include <bits/stdc++.h>
using namespace std;
#define MAX_LINE_LENGTH 1000
struct card
{
    int id;
    vector<int> winVals;
    vector<int> candVals;
    string rawLine;
};

vector<int> cardHasTheseRight(card c)
{
    vector<int> v;
    for (int i = 0; i < c.winVals.size(); i++)
    {
        for (int j = 0; j < c.candVals.size(); j++)
        {
            if (c.winVals[i] == c.candVals[j])
            {
                v.push_back(c.winVals[i]);
            }
        }
    }
    return v;
}

int getScoreOfCard(card c)
{
    vector<int> hasRight = cardHasTheseRight(c);
    if (hasRight.size() == 0)
    {
        return 0;
    }
    else if (hasRight.size() == 1)
    {
        return 1;
    }
    int res = 1;
    for (int i = 1; i < hasRight.size(); i++)
    {
        res *= 2;
    }
    return res;
}

int solvePart1(vector<card> cards)
{
    int sum = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        sum += getScoreOfCard(cards[i]);
    }
    return sum;
}

int main()
{
    char line[MAX_LINE_LENGTH];
    int x, counter;
    vector<string> v;
    vector<card> cards;
    counter = 0;
    vector<int> idsOfWonCards;
    while (cin.getline(line, MAX_LINE_LENGTH) && ++counter)
    {
        card c;
        c.rawLine = line;
        c.id = counter;

        stringstream ss;
        string s;
        bool hasSeenPipe = false;
        ss << line;

        // Consume card ID (lol)
        ss >> s >> s;
        while (!ss.eof())
        {
            ss >> s;
            if (s == "|")
            {
                hasSeenPipe = true;
            }
            else if (stringstream(s) >> x)
            {
                // cout << x << endl;
                hasSeenPipe ? c.candVals.push_back(x) : c.winVals.push_back(x);
            }
        }
        cards.push_back(c);
        int hasTheseRight = cardHasTheseRight(c).size();
        cout << "Card " << c.id << " has " << hasTheseRight << " right" << endl;
    }
    cout << "Part 1: " << solvePart1(cards) << endl;
}