#include <bits/stdc++.h>
using namespace std;
int main()
{
    char dir;
    int val;
    string hash;
    vector<pair<int, int>> borderPoints;
    int currX = 0, currY = 0;
    while (cin >> dir >> val >> hash)
    {
        cout << dir << endl;
        cout << val << endl;
        cout << hash << endl;
        switch (dir)
        {
        case 'U':
            for (int i = 0; i < val; i++)
            {
                currY++;
                borderPoints.push_back(make_pair(currX, currY));
            }
            break;
        case 'D':
            for (int i = 0; i < val; i++)
            {
                currY--;
                borderPoints.push_back(make_pair(currX, currY));
            }
            break;
        case 'R':
            for (int i = 0; i < val; i++)
            {
                currX++;
                borderPoints.push_back(make_pair(currX, currY));
            }
            break;
        case 'L':
            for (int i = 0; i < val; i++)
            {
                currX--;
                borderPoints.push_back(make_pair(currX, currY));
            }
            break;

        default:
            cout << "Invalid direction" << endl;
            break;
        }
    }
    cout << "borderPoints.size() = " << borderPoints.size() << endl;
}