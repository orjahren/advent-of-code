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
            break;

        default:
            cout << "Invalid direction" << endl;
            break;
        }
    }
    cout << "borderPoints.size() = " << borderPoints.size() << endl;

    // find all points inside the border
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
    for (auto point : borderPoints)
    {
        minX = min(minX, point.first);
        maxX = max(maxX, point.first);
        minY = min(minY, point.second);
        maxY = max(maxY, point.second);
    }
    cout << "minX = " << minX << endl;
    cout << "maxX = " << maxX << endl;
    cout << "minY = " << minY << endl;
    cout << "maxY = " << maxY << endl;

    // create a 2D array
    char **hullMatrix = new char *[maxX - minX + 1];
    // int **arr = new int *[maxX - minX + 1];
    for (int i = 0; i < maxX - minX + 1; i++)
    {
        hullMatrix[i] = new char[maxY - minY + 1];
    }

    // initialize all elements to 0
    for (int i = 0; i < maxX - minX + 1; i++)
    {
        for (int j = 0; j < maxY - minY + 1; j++)
        {
            hullMatrix[i][j] = '.';
        }
    }

    // mark all border points as 1
    for (auto point : borderPoints)
    {
        // arr[point.first - minX][point.second - minY] = '#';
        hullMatrix[point.first - minX][point.second - minY] = '#';
    }

    // print the array
    for (int i = 0; i < maxX - minX + 1; i++)
    {
        for (int j = 0; j < maxY - minY + 1; j++)
        {
            // cout << hullMatrix[i][j] << " ";
            cout << hullMatrix[i][j];
        }
        cout << endl;
    }
    cout << "Gjør flood filll" << endl;

    // find a point inside the border
    int insideX = 0, insideY = 0;
    for (int i = 0; i < maxX - minX + 1; i++)
    {
        for (int j = 0; j < maxY - minY + 1; j++)
        {
            if (hullMatrix[i][j] == '#')
            {
                insideY = i;
                insideX = j;
                break;
            }
        }
    }

    cout << "a point inside the border is: " << insideX << ", " << insideY << endl;

    // flood fill
    queue<pair<int, int>> q;
    // q.push(make_pair(insideX, insideY));
    // q.push(make_pair(1, 1));
    // q.push(make_pair(21, 6));
    q.push(make_pair(6, 21));
    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();
        int x = curr.first;
        int y = curr.second;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        if (x < 0 || x >= maxX - minX + 1 || y < 0 || y >= maxY - minY + 1)
        {
            cout << "Continuer på første" << endl;
            continue;
        }
        if (hullMatrix[x][y] == '#')
        {
            cout << "Continuer på andre" << endl;
            continue;
        }
        hullMatrix[x][y] = '#';
        q.push(make_pair(x + 1, y));
        q.push(make_pair(x - 1, y));
        q.push(make_pair(x, y + 1));
        q.push(make_pair(x, y - 1));
    }

    int part1 = 0;
    // print the array
    for (int i = 0; i < maxX - minX + 1; i++)
    {
        for (int j = 0; j < maxY - minY + 1; j++)
        {
            char c = hullMatrix[i][j];
            // cout << c << " ";
            cout << c;
            part1 += (c == '#');
        }
        cout << endl;
    }
    cout << "Part 1: " << part1 << endl;
}
// First ans: 5796. Too low.
// 2nd: 34329. Correct.