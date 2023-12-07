#include <bits/stdc++.h>
using namespace std;
enum HandEnum
{
    five = 7,
    four = 6,
    house = 5,
    three = 4,
    twoPairs = 3,
    onePair = 2,
    highCard = 1
};

int getEnumForHand(string hand)
{
    if (hand == "five-of-a-kind")
    {
        return five;
    }
    else if (hand == "four-of-a-kind")
    {
        return four;
    }
    else if (hand == "full-house")
    {
        return house;
    }
    else if (hand == "three-of-a-kind")
    {
        return three;
    }
    else if (hand == "two-pairs")
    {
        return twoPairs;
    }
    else if (hand == "pair")
    {
        return onePair;
    }
    else
    {
        return highCard;
    }
}

int main()
{
    string hand;
    int val;
    while (cin >> hand)
    {
        cin >> val;
        cout << hand << " " << val << endl;
    }
}