#include <bits/stdc++.h>
using namespace std;
#define MAX_LINE_LENGTH 1000
int sum(vector<int> &v)
{
    int res = 0;
    for (int i = 0; i < v.size(); i++)
        res += v[i];
    return res;
}

int getScoreOfCard(int &c)
{
    if (c > 1)
    {
        int res = 1;
        for (int i = 1; i < c; i++)
            res *= 2;
        return res;
    }
    return c;
}

int solvePart1(vector<int> &cards)
{
    int res = 0;
    for (int i = 0; i < cards.size(); i++)
        res += getScoreOfCard(cards[i]);
    return res;
}

int solvePart2(vector<int> &cards)
{
    vector<int> cardCounts = vector<int>(cards.size(), 1);
    vector<int> cardsConsumed = vector<int>(cards.size(), 0);
    for (int i = 0; i < cards.size(); i++)
    {
        for (int winId = i + 1; winId <= min(i + cards[i], (int)cards.size()); winId++)
            cardCounts[winId] += cardCounts[i] - cardsConsumed[i];
        cardsConsumed[i] += cardCounts[i];
    }
    return sum(cardCounts);
}

int cardHasHowManyRight(vector<int> &winVals, vector<int> &candVals)
{
    int res = 0;
    sort(candVals.begin(), candVals.end());
    for (int i = 0; i < winVals.size(); i++)
        if (binary_search(candVals.begin(), candVals.end(), winVals[i]))
            res++;
    return res;
}

vector<int> initCardsFromIO()
{
    vector<int> cardsByHowManyRight;
    char line[MAX_LINE_LENGTH];
    int x;
    while (cin.getline(line, MAX_LINE_LENGTH))
    {
        vector<int> winVals, candVals;
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
                hasSeenPipe ? candVals.push_back(x) : winVals.push_back(x);
        }
        cardsByHowManyRight.push_back(cardHasHowManyRight(winVals, candVals));
    }
    return cardsByHowManyRight;
}
int main()
{
    vector<int> cards = initCardsFromIO();
    cout << "Part 1: " << solvePart1(cards) << endl;
    cout << "Part 2: " << solvePart2(cards) << endl;
}