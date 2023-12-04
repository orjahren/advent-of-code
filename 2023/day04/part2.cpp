#include <bits/stdc++.h>
using namespace std;
#define MAX_LINE_LENGTH 1000
struct card
{
    int id;
    vector<int> winVals;
    vector<int> candVals;
};

vector<int> cardHasTheseRight(card &c)
{
    vector<int> v;
    for (int i = 0; i < c.winVals.size(); i++)
        for (int j = 0; j < c.candVals.size(); j++)
            if (c.winVals[i] == c.candVals[j])
                v.push_back(c.winVals[i]);
    return v;
}
int sum(vector<int> &v)
{
    int res = 0;
    for (int i = 0; i < v.size(); i++)
        res += v[i];
    return res;
}

int getScoreOfCard(card &c)
{
    vector<int> hasRight = cardHasTheseRight(c);
    if (hasRight.size() == 0)
        return 0;
    else if (hasRight.size() == 1)
        return 1;
    int res = 1;
    for (int i = 1; i < hasRight.size(); i++)
        res *= 2;
    return res;
}

int solvePart1(vector<card> &cards)
{
    int res = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        res += getScoreOfCard(cards[i]);
    }
    return res;
}

int solvePart2(vector<card> &cards)
{
    vector<int> cardCounts = vector<int>(cards.size(), 1);
    vector<int> cardsConsumed = vector<int>(cards.size(), 0);
    bool isDone;
    do
    {
        isDone = true;
        for (int i = 0; i < cards.size(); i++)
        {
            card &c = cards[i];
            if (cardCounts[c.id] != cardsConsumed[c.id])
            {
                vector<int> hasRight = cardHasTheseRight(c);
                for (int winId = c.id + 1; winId <= min(c.id + hasRight.size(), cards.size()); winId++)
                    cardCounts[winId] += cardCounts[c.id] - cardsConsumed[c.id];
                cardsConsumed[c.id] += cardCounts[c.id];
                isDone = false;
            }
        }
    } while (!isDone);
    return sum(cardCounts);
}

int main()
{
    char line[MAX_LINE_LENGTH];
    vector<card> cards;
    int x, counter = 0;
    while (cin.getline(line, MAX_LINE_LENGTH) && ++counter)
    {
        card c;
        c.id = counter - 1;
        stringstream ss;
        string s;
        bool hasSeenPipe = false;
        ss << line;
        // Consume card ID (lol)
        ss >> s >> s;
        while (!ss.eof())
        {
            ss >> s;
            if (!hasSeenPipe && s == "|")
                hasSeenPipe = true;
            else if (stringstream(s) >> x)
                hasSeenPipe ? c.candVals.push_back(x) : c.winVals.push_back(x);
        }
        cards.push_back(c);
    }
    cout << "Part 1: " << solvePart1(cards) << endl;
    cout << "Part 2: " << solvePart2(cards) << endl;
}