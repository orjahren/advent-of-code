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
        switch (dir)
        {
        case 'U':
            for (int i = 0; i < val; i++)
            {
                currY--;
                borderPoints.push_back(make_pair(currX, currY));
            }
            break;
        case 'D':
            for (int i = 0; i < val; i++)
            {
                currY++;
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
        }
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
    for (auto point : borderPoints)
    {
        minX = min(minX, point.first);
        maxX = max(maxX, point.first);
        minY = min(minY, point.second);
        maxY = max(maxY, point.second);
    }

    char **hullMatrix = new char *[maxX - minX + 1];
    for (int i = 0; i < maxX - minX + 1; i++)
        hullMatrix[i] = new char[maxY - minY + 1];

    for (int i = 0; i < maxX - minX + 1; i++)
        for (int j = 0; j < maxY - minY + 1; j++)
            hullMatrix[i][j] = '.';

    for (auto point : borderPoints)
        hullMatrix[point.first - minX][point.second - minY] = '#';
    queue<pair<int, int>> q;

    // Test
    // q.push(make_pair(1, 1));

    // Prod
    q.push(make_pair(6, 21));
    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();
        int x = curr.first;
        int y = curr.second;
        if (x < 0 || x >= maxX - minX + 1 || y < 0 || y >= maxY - minY + 1 || hullMatrix[x][y] == '#')
            continue;
        hullMatrix[x][y] = '#';
        q.push(make_pair(x + 1, y));
        q.push(make_pair(x - 1, y));
        q.push(make_pair(x, y + 1));
        q.push(make_pair(x, y - 1));
    }

    int part1 = 0;
    for (int i = 0; i < maxX - minX + 1; i++)
    {
        for (int j = 0; j < maxY - minY + 1; j++)
        {
            char c = hullMatrix[i][j];
            part1 += (c == '#');
        }
    }
    cout << "Part 1: " << part1 << endl;
}