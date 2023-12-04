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

int getScoreOfCard(card &c)
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
    // TODO: Burde være mulig å flytte denne løkkens funksjonalitet til main
    for (int i = 0; i < cards.size(); i++)
    {
        card &c = cards[i];
        // c.wonCands = c.candVals;
    }
    vector<int> cardCounts = vector<int>(cards.size(), 1);
    vector<int> cardsConsumed = vector<int>(cards.size(), 0);
    bool somethingWasWon = false;
    do
    {
        somethingWasWon = false;
        for (int i = 0; i < cards.size(); i++)
        {
            card &c = cards[i];
            if (cardCounts[c.id] == cardsConsumed[c.id])
            {
                cout << "Skipping card " << c.id + 1 << " because it has been consumed" << endl;
                continue;
            }

            vector<int> hasRight = cardHasTheseRight(c);
            cout << c.id + 1 << " har " << hasRight.size() << " riktige" << endl;
            int howManyAreWon = cardCounts[c.id] - cardsConsumed[c.id];
            cout << "We have " << cardCounts[c.id] << " of the winner" << endl;
            cout << "Consumption: " << cardsConsumed[c.id] << endl;
            // for (int winId = c.id + 1; winId <= min(c.id + hasRight.size(), cards.size() + 1); winId++)
            for (int winId = c.id + 1; winId <= min(c.id + hasRight.size(), cards.size()); winId++)
            {
                cout << "Card " << c.id + 1 << " won " << howManyAreWon << " of " << winId + 1 << endl;
                cardCounts[winId] += howManyAreWon;
                somethingWasWon = true;
            }
            // cardCounts[c.id]--;

            // cardsConsumed[c.id]++;
            cardsConsumed[c.id] += cardCounts[c.id];
            cout << "--" << endl;
        }

    } while (somethingWasWon);
    int res = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        cout << "\n \t ### Card " << i + 1 << " ###" << endl;
        // int score = cardCounts[i + 1];
        //  score += cardsConsumed[i + 1];
        // int score = cardsConsumed[i + 1];
        // score -= cardCounts[i + 1];
        // int score = cardCounts[i] - cardsConsumed[i];
        int score = cardCounts[i];
        cout << "Has " << cardCounts[i] << " of " << i + 1 << endl;
        cout << "Has consumed " << cardsConsumed[i] << " of " << i + 1 << endl;
        cout << "Score for card " << i + 1 << " is " << score << endl;
        res += score;
    }
    return res;

    /*
    int res = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        cout << "\n \t ### Card " << i + 1 << " ###" << endl;
        // int score = cardCounts[i + 1];
        //  score += cardsConsumed[i + 1];
        // int score = cardsConsumed[i + 1];
        // score -= cardCounts[i + 1];
        int score = cardCounts[i + 1] - cardsConsumed[i + 1];
        cout << "Has " << cardCounts[i + 1] << " of " << i + 1 << endl;
        cout << "Has consumed " << cardsConsumed[i + 1] << " of " << i + 1 << endl;
        cout << "Score for card " << i + 1 << " is " << score << endl;
        res += score;
    }
    return res;
    */
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
            {
                hasSeenPipe = true;
            }
            else if (stringstream(s) >> x)
            {
                hasSeenPipe ? c.candVals.push_back(x) : c.winVals.push_back(x);
            }
        }
        cards.push_back(c);
    }
    cout << "Part 1: " << solvePart1(cards) << endl;
    cout << "Part 2: " << solvePart2(cards) << endl;
}